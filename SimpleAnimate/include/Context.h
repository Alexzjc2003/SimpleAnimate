#pragma once

namespace SA
{
  class Context
  {
  public:
    Context();

    void loop(void (*func)());

  private:
    int _glfw_init = GLFW_FALSE;
    void initGLFW();
  };
} // namespace SA
