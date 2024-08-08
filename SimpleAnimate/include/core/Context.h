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

		Window* pWindow;
	};

} // namespace SA