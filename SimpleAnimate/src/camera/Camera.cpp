#include "pch.h"
#include "camera/Camera.h"
#include "util/Logger.h"
using namespace SA;

Camera::Camera()
{
}

Camera::Camera(float _top, float _bottom, float _left, float _right, float _near, float _far)
{
  frustum.top = _top;
  frustum.bottom = _bottom;
  frustum.left = _left;
  frustum.right = _right;
  frustum.near = _near;
  frustum.far = _far;
}

glm::mat4 Camera::getViewMatrix()
{
  return glm::lookAt(
      position,
      position + getDirLocal(),
      static_cast<glm::mat3>(getQuaternion()) * default_up);

}

glm::mat4 Camera::getProjMatrix()
{
  // projection matrix for any
  // camera based on frustum
  return glm::frustum(
      frustum.left, frustum.right,
      frustum.bottom, frustum.top,
      frustum.near, frustum.far);
}
