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
  logger.log(getPosition(),"pos");
  logger.log(getDirection(),"dir");

  return glm::lookAt(
      getPosition(),
      getPosition() + getDirection(),
      glm::mat3(getModelLocal()) * glm::vec3(0, 1, 0));
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
