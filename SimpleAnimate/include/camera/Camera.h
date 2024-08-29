#pragma once

#include <glm/glm.hpp>
#include <core/Object3D.h>
#include <def.h>

#include <glm/glm.hpp>

namespace SA
{
  class SA_API Camera : public Object3D
  {
  public:
    Camera();
    Camera(float _top, float _bottom, float _left, float _right, float _near, float _far);

    glm::mat4 getViewMatrix();
    virtual glm::mat4 getProjMatrix();

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