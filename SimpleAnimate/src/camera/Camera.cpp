#include "pch.h"
#include "camera/Camera.h"

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
