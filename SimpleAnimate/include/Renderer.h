#pragma once

#include <control/Control.h>
#include <Scene.h>
#include <glfw/glfw3.h>
#include <camera/Camera.h>
#include <Object3D.h>

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
    void render(Scene &scene, Camera &camera);

  private:
    GLFWwindow *pWindow;

    void renderObject(Object3D &object, Camera& camera) const;
  };
} // namespace SA
