#pragma once

#include <control/control.h>
#include <glfw/glfw3.h>

namespace SA
{
  namespace RENDERER
  {
    constexpr unsigned int WINDOW_WIDTH = 1920;
    constexpr unsigned int WINDOW_HEIGHT = 1080;
  }

  class Renderer
  {
  public:
    Renderer();
    void useControl(Control &control);

  private:
    GLFWwindow *pWindow;


  };
} // namespace SA
