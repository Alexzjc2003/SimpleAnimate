#pragma once

#include <control/Control.h>
#include <Scene.h>
#include <glfw/glfw3.h>
#include <camera/Camera.h>
#include <Object3D.h>

namespace SA
{
  class SA_API Renderer
  {
  public:
    Renderer();
    void render(Scene &scene, Camera &camera);

  private:
    void renderObject(Object3D &object, Camera& camera) const;
  };
} // namespace SA
