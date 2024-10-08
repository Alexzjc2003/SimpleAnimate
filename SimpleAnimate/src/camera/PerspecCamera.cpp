#include "pch.h"
#include "camera/PerspecCamera.h"

#include <cmath>

using namespace SA;

PerspecCamera::PerspecCamera() {}

PerspecCamera::PerspecCamera(float _fov, float _aspect, float _near, float _far)
    : fov(_fov),
      aspect(_aspect)
{
  float _width = _near * tan(_fov / 2);
  float _height = _width / _aspect;

  frustum.top = _height;
  frustum.bottom = -_height;
  frustum.left = -_width;
  frustum.right = _width;
  frustum.near = _near;
  frustum.far = _far;
}

glm::mat4 PerspecCamera::getProjMatrix()
{
  return glm::perspective(
      fov,
      aspect,
      frustum.near, frustum.far);
}
