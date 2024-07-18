#pragma once
#include <vector>

namespace SA
{
  class Context
  {
  public:
    Context();

    void loop(void (*func)());
    double getDelta();
    double getTime();

  private:
    int _glfw_init = GLFW_FALSE;
    void initGLFW();

    double timeDelta;
    double timePrev;
    // std::vector<void (*)()> _loop_funs;
  };
} // namespace SA
