#pragma once
#include "def.h"
#include "light/Light.h"

namespace SA
{
  class SA_API SpotLight : public Light
  {
  public:
    SpotLight(
        const Color &_color,
        const glm::vec3 &_position = glm::vec3(0.0),
        const glm::vec3 &_direction = Object3D::default_front,
        const float &_cutoff_outer = 30.0, // outer cutoff in degrees
        const float &_cutoff_inner = 5.0,  // inner cutoff in degrees
        const glm::vec3 &_atten = glm::vec3(1.0, 0.0, 0.0));
    SpotLight(
        const glm::mat3 &_ads,
        const glm::vec3 &_position = glm::vec3(0.0),
        const glm::vec3 &_direction = Object3D::default_front,
        const float &_cutoff_outer = 30.0, // outer cutoff in degrees
        const float &_cutoff_inner = 5.0,  // inner cutoff in degrees
        const glm::vec3 &_atten = glm::vec3(1.0, 0.0, 0.0));

    glm::vec2 cutoff;

    virtual void updateUniform();
  };
} // namespace SA
