#pragma once
#include "def.h"
#include "light/Light.h"

namespace SA
{
  class SA_API DirectionalLight : public Light
  {
  public:
    DirectionalLight(
        const Color &_color,
        const glm::vec3 &_direction = Object3D::default_front,
        const glm::vec3 &_atten = glm::vec3(1.0, 0.0, 0.0));
    DirectionalLight(
        const glm::mat3 &_ads,
        const glm::vec3 &_direction = Object3D::default_front,
        const glm::vec3 &_atten = glm::vec3(1.0, 0.0, 0.0));
  };
} // namespace SA
