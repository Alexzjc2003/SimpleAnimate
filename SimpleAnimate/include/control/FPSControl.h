#pragma once

#include <control/control.h>

namespace SA
{
  class SA_API FPSControl : public Control
  {
  public:
    FPSControl();

    double move_speed = 1;
    double mouse_sensitivity = 1;

    virtual void keyCallback(int key, int scancode, int action, int mods);
    virtual void mouseMoveCallback(double x_pos, double y_pos);
    virtual void scrollCallback(double x_offset, double y_offset);

    virtual void inputLoop(double delta);

  protected:
  private:
    virtual void onBindWindow();
    struct
    {
      bool left = false;
      bool right = false;
      bool forward = false;
      bool backward = false;
      bool up = false;
      bool down = false;

      double pitch = 0;
      double yaw = 0;
    } move;
    struct
    {
      double x = 0;
      double y = 0;
      double w = 0;
      double h = 0;
    } mouse;
  };
}