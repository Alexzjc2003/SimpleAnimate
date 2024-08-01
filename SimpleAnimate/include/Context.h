#pragma once
#include <vector>
#include <def.h>
#include <GLFW/glfw3.h>

namespace SA
{
	class SA_API Context
	{
	public:
		Context();
		template <typename Func>
		void loop( Func&& func );
		double getDelta();
		double getTime();

		GLFWwindow* getWindow() const;

	private:
		int _glfw_init = GLFW_FALSE;

		/* Init glfw
		 * Feel free to call this, as this will do nothing
		 * if glfw has been inited.
		 */
		void initGLFW();

		GLFWwindow* pWindow;


		double timeDelta;
		double timePrev;
	};


	// inline template functions to expose
	template <typename Func>
	inline void Context::loop( Func&& func )
	{
		while ( !glfwWindowShouldClose( pWindow ) )
		{
			if ( glfwGetKey( pWindow , GLFW_KEY_ESCAPE ) == GLFW_PRESS )
			// we explicitly check if the window should close
			{
				glfwSetWindowShouldClose( pWindow , true );
			}

			double _time = glfwGetTime();
			timeDelta = _time - timePrev;
			timePrev = _time;


			func();


			glfwSwapBuffers( pWindow );
			glfwPollEvents();
		}
	}

} // namespace SA