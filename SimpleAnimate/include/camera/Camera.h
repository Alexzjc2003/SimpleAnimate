#pragma once

#include <glm/glm.hpp>
#include <Object3D.h>

#include <glm/glm.hpp>

namespace SA
{
  class Camera : public Object3D
  {
  public:
    Camera();
    Camera(float _top, float _bottom, float _left, float _right, float _near, float _far);

  protected:
    struct
    {
      float top;
      float bottom;
      float left;
      float right;
      float near;
      float far;
    } frustum;
  };

} // namespace SA