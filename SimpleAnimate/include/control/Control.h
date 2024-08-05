/*
 * This is a control class that relies on glfw to work
 */

#pragma once

#include <functional>

#include <core/Object3D.h>
#include <core/Context.h>
#include <def.h>

#include <glfw/glfw3.h>

namespace SA
{
  class SA_API Control
  {
  public:
    void bindContext(Context *pContext);
    void bindObject(Object3D *pObject);

    virtual void keyCallback(GLFWwindow *pWindow, int key, int scancode, int action, int mods) = 0;
    virtual void mouseMoveCallback(GLFWwindow *pWindow, double x_pos, double y_pos) = 0;
    virtual void scrollCallback(GLFWwindow *pWindow, double x_offset, double y_offset) = 0;

    virtual void inputLoop(Context* pContext) = 0;

  protected:
    Control();
    Object3D *pObject;
    Context *pContext;

    virtual void bindWindow(GLFWwindow *pWindow);
    virtual void onBindWindow(GLFWwindow *pWindow) = 0;
  };
} // namespace SA
