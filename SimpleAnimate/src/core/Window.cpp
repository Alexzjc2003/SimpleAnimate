#include "pch.h"
#include "core/Window.h"
#include "core/Proxy.h"
#include "core/Context.h"
#include "control/Control.h"

using namespace SA;

int Window::count = 0;

Window::Window(
	int _width, int _height,
	int _pos_x, int _pos_y,
	std::string _title,
	bool _show)
	: title(_title),
	size({ _width, _height }),
	pos({ _pos_x, _pos_y }),
	show(_show),
	living(true),
	context(this),
	pWindow(nullptr),
	pControl(nullptr)
{
	// init glfw if necessary
	if (!count)
		glfwInit();
	++count;

	// create glfw window
	create();

#ifdef SA_USING_PROXY
	pos.onSet = [this](auto _pos)
	{ glfwSetWindowPos(this->pWindow, _pos.x, _pos.y); this->pos.copy(_pos); };
	size.onSet = [this](auto _size)
	{ glfwSetWindowSize(this->pWindow, _size.width, _size.height); this->size.copy(_size); };
	show.onSet = [this](auto _show)
	{
		if (_show)
			glfwShowWindow(this->pWindow);
		else
			glfwHideWindow(this->pWindow);
		show.copy(_show);
	};
	living.onSet = [this](auto _living)
	{
		if (this->living == _living)
			return;

		// from dead to live
		if (_living)
			this->create();

		// from live to dead
		if (!_living)
		{
			glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
			glfwPollEvents();
			this->destroy();
		}
	};

	pos.onGet = [this]()
	{
		int x, y;
		glfwGetWindowPos(this->pWindow, &x, &y);
		this->pos.copy({ x, y });
		return pos.clone();
	};
	size.onGet = [this]()
	{
		int w, h;
		glfwGetWindowSize(this->pWindow, &w, &h);
		this->size.copy({ w, h });
		return size.clone();
	};
	living.onGet = [this]()
	{
		this->living.copy(!glfwWindowShouldClose(this->pWindow));
		return living.clone();
	};

#else
	glfwSetWindowPosCallback(pWindow, [this](GLFWwindow* pWindow, int _x, int _y)
	{ this->pos.x = _x; this->pos.y = _y; });
	glfwSetWindowSizeCallback(pWindow, [this](GLFWwindow* pWindow, int _w, int _h)
	{ this->size.width = _w; this->size.height = _h; });
#endif

	// setup callback functions
	keyCallback = [this](int _key, int _scancode, int _action, int _mods)
	{
		// Each window should be able to close by pressing ESC
		if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
			glfwSetWindowShouldClose(pWindow, GLFW_TRUE);

		if (this->pControl)
			this->pControl->keyCallback(_key, _scancode, _action, _mods);
	};
	scrollCallback = [this](double _x_offset, double _y_offset)
	{if (this->pControl) this->pControl->scrollCallback(_x_offset, _y_offset); };
	cursorPosCallback = [this](double _x_pos, double _y_pos)
	{if (this->pControl) this->pControl->mouseMoveCallback(_x_pos, _y_pos); };

	loop = [this](double _delta)
	{if (this->pControl) this->pControl->inputLoop(_delta); };

	// register callbacks
	glfwSetKeyCallback(pWindow, _glfw_key_callback);
	glfwSetScrollCallback(pWindow, _glfw_scroll_callback);
	glfwSetCursorPosCallback(pWindow, _glfw_cursor_pos_callback);
}

Window::~Window()
{
	--count;
	if (!count)
		glfwTerminate();
}

#ifndef SA_USING_PROXY
void Window::resize(int _width, int _height)
{
	glfwSetWindowSize(pWindow, _width, _height);
}

void Window::moveTo(int _pos_x, int _pos_y)
{
	glfwSetWindowPos(pWindow, _pos_x, _pos_y);
}
#endif

void Window::bindControl(Control* control)
{
	pControl = control;
}

void Window::create()
{
	if (pWindow)
		return;

	// create window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, show);

	auto [_width, _height] = size.clone();
	auto [_pos_x, _pos_y] = pos.clone();
	pWindow = glfwCreateWindow(_width, _height, title.c_str(), NULL, NULL);
	glfwSetWindowPos(pWindow, _pos_x, _pos_y);
	glfwSetWindowUserPointer(pWindow, this);

	// setup context
	context.setup();
	int _w, _h;
	glfwGetFramebufferSize(pWindow, &_w, &_h);
	context.viewport = { 0, 0, _w, _h };
}

void Window::destroy()
{
	if (!pWindow)
		return;
	glfwDestroyWindow(pWindow);
	pWindow = nullptr;
}

// raw glfw form callbacks
void Window::_glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (pWindow && pWindow->keyCallback)
		pWindow->keyCallback(key, scancode, action, mods);
}

void Window::_glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (pWindow && pWindow->scrollCallback)
		pWindow->scrollCallback(xoffset, yoffset);
}

void Window::_glfw_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window* pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (pWindow && pWindow->cursorPosCallback)
		pWindow->cursorPosCallback(xpos, ypos);
}
