#include "pch.h"
#include "core/Context.h"
#include "debug.h"

using namespace SA;

SA_API Context::Context()
{
	// init glfw
	initGLFW();

	// create window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	pWindow = glfwCreateWindow(1920, 1080, "SimpleAnimate", NULL, NULL);
	if (!pWindow)
	{
		throw "Context: Fail to create window";
	}
	std::cout << "GLFW window created" << std::endl;

	glfwSetWindowPos(pWindow, 400, 200);
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw "Context: Fail to initialize OpenGL context";
	}
	std::cout << "GLAD load complete" << std::endl;

	glViewport(0, 0, 1920, 1080);
	glEnableDebug();
}

double Context::getDelta() { return timeDelta; }
double Context::getTime() { return glfwGetTime(); }

GLFWwindow* Context::getWindow() const { return pWindow; }

void Context::initGLFW()
{
	if (_glfw_init == GLFW_TRUE)
		return;

	_glfw_init = glfwInit();
	if (_glfw_init == GLFW_FALSE)
	{
		glfwTerminate();
		throw "Renderer::initGLFW: Fail to init glfw";
	}
	std::cout << "GLFW init complete" << std::endl;
}