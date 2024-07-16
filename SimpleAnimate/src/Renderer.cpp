#include "pch.h"
#include "Renderer.h"

using namespace SA;

Renderer::Renderer()
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  pWindow = glfwCreateWindow(RENDERER::WINDOW_WIDTH, RENDERER::WINDOW_HEIGHT, "SimpleAnimate", NULL, NULL);
  glfwSetWindowPos(pWindow, 400, 200);
  glfwMakeContextCurrent(pWindow);
}

void Renderer::useControl(Control &control)
{
  control.bindContext(pWindow);
}

