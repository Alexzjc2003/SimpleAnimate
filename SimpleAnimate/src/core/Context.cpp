#include "pch.h"
#include "core/Context.h"
#include "core/Proxy.h"
#include "core/Window.h"
#include "debug.h"

using namespace SA;

Context::Context(Window* window) :
	pWindow(window),
	loop(),
	viewport({ 0, 0, 0, 0 })
{
	viewport.onSet = [](auto _viewport)
	{
		glViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
	};

	loop.onGet = [this]()
	{
		return [this](double)
		{
			while (pWindow->living)
			{
				double _time = glfwGetTime();
				timeDelta = _time - timePrev;
				timePrev = _time;

				loop.clone()(timeDelta);

				glfwSwapBuffers(pWindow->pWindow);
				glfwPollEvents();
			}
		};
	};
}

void Context::setup()
{
	glfwMakeContextCurrent(pWindow->pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw "Context: Fail to initialize OpenGL context";
	}
	std::cout << "GLAD load complete" << std::endl;

	glEnableDebug();
}

double Context::getDelta() const { return timeDelta; }
double Context::getTime() const { return timePrev; }
