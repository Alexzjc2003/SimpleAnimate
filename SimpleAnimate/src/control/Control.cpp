#include "pch.h"
#include "control/Control.h"
#include "core/Window.h"

using namespace SA;

Control::Control() : pObject(nullptr), pWindow(nullptr)
{
}

void Control::bindObject(Object3D* pObject) { this->pObject = pObject; }
void Control::bindWindow(Window* pWindow)
{
	this->pWindow = pWindow;


	pWindow->bindControl(this);
	onBindWindow();
}

void Control::onBindWindow() {}

// void Control::keyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods) {}
// void Control::mouseMoveCallback(GLFWwindow* pWindow, double x_pos, double y_pos) {}
// void Control::scrollCallback(GLFWwindow* pWindow, double x_offset, double y_offset) {}
// void Control::inputLoop(Context* pContext) {}