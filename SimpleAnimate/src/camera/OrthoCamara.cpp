#include "OrthoCamera.h"

using namespace SA;

OrthoCamera::OrthoCamera() {}

OrthoCamera::OrthoCamera(float _width, float _height, float _near, float _far)
    : Camera(_height / 2, -_height / 2, -_width / 2, _width / 2, _near, _far)
{
}

