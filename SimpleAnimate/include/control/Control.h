/*
 * This is a control class that relies on glfw to work
 */

#pragma once

#include <functional>

#include <Object3D.h>

#include <glfw/glfw3.h>

namespace SA
{
  class Control
  {
  public:
    void bindContext(GLFWwindow *pWindow);
    void bindObject(Object3D *pObject);

    virtual void keyCallback(GLFWwindow *pWindow, int key, int scancode, int action, int mods);
    virtual void mouseMoveCallback(GLFWwindow *pWindow, double x_pos, double y_pos);
    virtual void scrollCallback(GLFWwindow *pWindow, double x_offset, double y_offset);

  protected:
    Control();
    Object3D *pObject;

  };
} // namespace SA
