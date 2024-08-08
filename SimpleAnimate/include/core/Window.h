/*
 * Wrapper for GLFWwindow
 */

#pragma once

#include <glfw/glfw3.h>
#include <functional>
#include <string>
#include <def.h>
#include <core/Proxy.h>
#include <core/Context.h>

namespace SA
{
	class SA_API Control;

	class SA_API Window
	{
	public:
		Window(
				int _width = 1024, int _height = 768,
				int _pos_x = 0, int _pos_y = 0,
				std::string _title = "SimpleAnimate Window @ Alexzjc2003",
				bool _show = true);
		~Window();

		friend class Context;

		void bindControl(Control *control);

		Context context;
		std::string title;
		struct _sa_window_size_t
		{
			int width;
			int height;
		};
		struct _sa_window_pos_t
		{
			int x;
			int y;
		};
#ifdef SA_USING_PROXY
		Proxy<_sa_window_size_t> size;
		Proxy<_sa_window_pos_t> pos;
		Proxy<bool> show;
		Proxy<bool> living;
#else
		bool show;
		void resize(int _width, int _height);
		void moveTo(int _pos_x, int _pos_y);
#endif

	protected:
		void create();
		void destroy();

		static int count;
		Control *pControl;
		GLFWwindow *pWindow;

		std::function<void(int, int, int, int)> keyCallback;
		std::function<void(double, double)> scrollCallback;
		std::function<void(double, double)> cursorPosCallback;
		// std::function<void()> loop;
		//  std::function<void()> renderCallback;

#ifndef SA_USING_PROXY
		_sa_window_size_t size;
		_sa_window_pos_t pos;
#endif

	private:
		static void _glfw_key_callback(GLFWwindow *, int, int, int, int);
		static void _glfw_scroll_callback(GLFWwindow *, double, double);
		static void _glfw_cursor_pos_callback(GLFWwindow *, double, double);
	};
} // namespace SA
