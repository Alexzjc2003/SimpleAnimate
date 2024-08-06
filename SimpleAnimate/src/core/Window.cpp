#include "pch.h"
#include "core/Window.h"

using namespace SA;

int SA::Window::count = 0;

SA::Window::Window(
    int _width, int _height,
    int _pos_x, int _pos_y,
    std::string _title,
    bool _show)
    : title(_title),
      size({_width, _height}),
      pos({_pos_x, _pos_y}),
      show(_show),
      context(),
      pControl(nullptr)
{
  // init glfw if necessary
  if (!count)
    glfwInit();
  ++count;

  // create window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  glfwWindowHint(GLFW_VISIBLE, _show);

  pWindow = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
  glfwSetWindowPos(pWindow, _pos_x, _pos_y);

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

  pos.onGet = [this]()
  {
    int x, y;
    glfwGetWindowPos(this->pWindow, &x, &y);
    this->pos.copy({x, y});
    return pos;
  };
  size.onGet = [this]()
  {
    int w, h;
    glfwGetWindowSize(this->pWindow, &w, &h);
    this->size.copy({w, h});
    return size;
  };

#else
  glfwSetWindowPosCallback(pWindow, [this](GLFWwindow *pWindow, int _x, int _y)
                           { this->pos.x = _x; this->pos.y =_y; });
  glfwSetWindowSizeCallback(pWindow, [this](GLFWwindow *pWindow, int _w, int _h)
                            { this->size.width = _w;this->size.height = _h; });
#endif

  // setup context
  context.setup(pWindow);
  int _w, _h;
  glfwGetFramebufferSize(pWindow, &_w, &_h);
  context.viewport = {0, 0, _w, _h};
}

SA::Window::~Window()
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

void SA::Window::bindControl(Control *control)
{
  pControl = control;
}