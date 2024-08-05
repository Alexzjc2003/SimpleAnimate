#include "pch.h"
#include "control/Control.h"

using namespace SA;

Control::Control() :
	pContext(nullptr),
	pObject(nullptr)
{
}

void Control::onBindWindow(GLFWwindow* pWindow) {}
void Control::bindWindow(GLFWwindow* pWindow)
{
	onBindWindow(pWindow);
	glfwSetWindowUserPointer(pWindow, this);

	glfwSetCursorPosCallback(pWindow, [](GLFWwindow* pWindow, double x_pos, double y_pos)
	{ static_cast<Control*>(glfwGetWindowUserPointer(pWindow))->mouseMoveCallback(pWindow, x_pos, y_pos); });
	glfwSetScrollCallback(pWindow, [](GLFWwindow* pWindow, double x_offset, double y_offset)
	{ static_cast<Control*>(glfwGetWindowUserPointer(pWindow))->scrollCallback(pWindow, x_offset, y_offset); });
	glfwSetKeyCallback(pWindow, [](GLFWwindow* pWindow, int key, int scancode, int action, int mods)
	{ static_cast<Control*>(glfwGetWindowUserPointer(pWindow))->keyCallback(pWindow, key, scancode, action, mods); });
}

void Control::bindContext(Context* pContext)
{
	this->pContext = pContext;
	if (pContext)
		bindWindow(pContext->getWindow());
}
void Control::bindObject(Object3D* pObject) { this->pObject = pObject; }

//void Control::keyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods) {}
//void Control::mouseMoveCallback(GLFWwindow* pWindow, double x_pos, double y_pos) {}
//void Control::scrollCallback(GLFWwindow* pWindow, double x_offset, double y_offset) {}
//void Control::inputLoop(Context* pContext) {}