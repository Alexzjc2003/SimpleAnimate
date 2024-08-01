#pragma once
#include "camera/Camera.h"

namespace SA
{
  class SA_API PerspecCamera : public Camera
  {
  public:
    PerspecCamera();
    PerspecCamera(float _fov, float _aspect, float _near, float _far);

    float fov;
    float aspect;

    virtual glm::mat4 getProjMatrix();
  };

} // namespace SA