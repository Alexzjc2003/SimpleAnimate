/*
 * Wrapper for GLFWwindow
 */

#include <glfw/glfw3.h>
#include <string>
#include <core/Proxy.h>
#include <core/Context.h>
#include <control/Control.h>
#include <def.h>

namespace SA
{
  class SA_API Window
  {
  public:
    Window(
        int _width = 1024, int _height = 768,
        int _pos_x = 0, int _pos_y = 0,
        std::string _title = "SimpleAnimate Window @ Alexzjc2003",
        bool _show = true);
    ~Window();

    void bindControl(Control *control);

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
#else
    bool show;
    void resize(int _width, int _height);
    void moveTo(int _pos_x, int _pos_y);
#endif

  protected:
    GLFWwindow *pWindow;
    static int count;
    Context context;
    Control *pControl;

#ifndef SA_USING_PROXY
    _sa_window_size_t size;
    _sa_window_pos_t pos;
#endif
  };
} // namespace SA
