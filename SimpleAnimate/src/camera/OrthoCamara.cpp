#include "pch.h"
#include "camera/OrthoCamera.h"

using namespace SA;

OrthoCamera::OrthoCamera() {}

OrthoCamera::OrthoCamera(float _width, float _height, float _near, float _far)
    : Camera(_height / 2, -_height / 2, -_width / 2, _width / 2, _near, _far)
{
}

glm::mat4 OrthoCamera::getProjMatrix()
{
  return glm::ortho(
      frustum.left, frustum.right,
      frustum.bottom, frustum.top);
}