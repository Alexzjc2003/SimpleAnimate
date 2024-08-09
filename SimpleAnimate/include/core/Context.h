#pragma once
#include <GLFW/glfw3.h>
#include <def.h>
#include <core/Proxy.h>

namespace SA
{
	class SA_API Window;

	class SA_API Context
	{
	public:
		Context(Window* window);

		Proxy<std::function<void(double)>> loop;
		void setup();
		
		double getDelta() const;
		double getTime() const;

		struct _sa_context_viewport_t
		{
			GLint x = 0;
			GLint y = 0;
			GLsizei w = 0;
			GLsizei h = 0;
		};
		Proxy<_sa_context_viewport_t>
			viewport;

	private:
		double timeDelta = 0;
		double timePrev = 0;

		Window* pWindow;
	};

} // namespace SA