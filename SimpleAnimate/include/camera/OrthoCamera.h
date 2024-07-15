#pragma once
#include <camera/Camera.h>

namespace SA
{
  class OrthoCamera : public Camera
  {
  public:
    OrthoCamera();
    OrthoCamera(float _width, float _height, float _near, float _far);
  
    virtual glm::mat4 getProjMatrix();
  
  
  };
} // namespace SA