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
  double _time = glfwGetTime();
  timeDelta = _time - timePrev;
  timePrev = _time;

  func();

  glfwPollEvents();
}

double Context::getDelta() { return timeDelta; }
double Context::getTime() { return glfwGetTime(); }

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