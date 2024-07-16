#include "pch.h"
#include "Context.h"

using namespace SA;

Context::Context()
{

  initGLFW();
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    throw "Context: Fail to initialize GLAD";
  }
}

void Context::loop(void (*func)())
{
  func();

  
  glfwPollEvents();
}

void Context::initGLFW()
{
  if (_glfw_init == GLFW_FALSE)
    return;

  _glfw_init = glfwInit();
  if (_glfw_init == GLFW_FALSE)
  {
    glfwTerminate();
    throw "Renderer::initGLFW: Fail to init glfw";
  }
}