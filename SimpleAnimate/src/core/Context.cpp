#include "pch.h"
#include "core/Context.h"
#include "debug.h"

using namespace SA;

Context::Context()
		: viewport({0, 0, 0, 0})
{
	viewport.onSet = [](auto _viewport)
	{
		glViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
	};
}

void Context::setup(GLFWwindow *pWindow)
{
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw "Context: Fail to initialize OpenGL context";
	}
	std::cout << "GLAD load complete" << std::endl;

	glEnableDebug();
}

double Context::getDelta() { return timeDelta; }
double Context::getTime() { return glfwGetTime(); }
