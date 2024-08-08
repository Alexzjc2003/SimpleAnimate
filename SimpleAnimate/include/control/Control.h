/*
 * This is a control class that relies on glfw to work
 */

#pragma once

#include <functional>

#include <def.h>
#include <glfw/glfw3.h>

namespace SA
{
  class SA_API Window;
  class SA_API Object3D;

  class SA_API Control
  {
  public:
    void bindWindow(Window *pWindow);
    void bindObject(Object3D *pObject);

    virtual void keyCallback(int key, int scancode, int action, int mods) = 0;
    virtual void mouseMoveCallback(double x_pos, double y_pos) = 0;
    virtual void scrollCallback(double x_offset, double y_offset) = 0;

    virtual void inputLoop(double delta) = 0;

  protected:
    virtual void onBindWindow();
    Control();
    Object3D *pObject;
    Window *pWindow;
  };
} // namespace SA
