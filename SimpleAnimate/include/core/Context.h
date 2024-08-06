#pragma once
#include <vector>
#include <def.h>
#include <GLFW/glfw3.h>
#include <core/Window.h>
#include <core/Proxy.h>

namespace SA
{
	class SA_API Context
	{
	public:
		Context();
		void setup(GLFWwindow *window);
		template <typename Func>
		void loop(Func &&func);
		double getDelta();
		double getTime();

		struct _sa_context_viewport_t
		{
			GLint x;
			GLint y;
			GLsizei w;
			GLsizei h;
		};
		Proxy<_sa_context_viewport_t>
				viewport;

	private:
		double timeDelta;
		double timePrev;
	};

	// inline template functions to expose
	template <typename Func>
	void Context::loop(Func &&func)
	{
		while (!glfwWindowShouldClose(pWindow))
		{
			if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			// we explicitly check if the window should close
			{
				glfwSetWindowShouldClose(pWindow, true);
			}

			double _time = glfwGetTime();
			timeDelta = _time - timePrev;
			timePrev = _time;

			func();

			glfwSwapBuffers(pWindow);
			glfwPollEvents();
		}
	}

} // namespace SA