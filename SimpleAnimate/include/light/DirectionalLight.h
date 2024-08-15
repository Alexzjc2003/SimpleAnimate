#pragma once
#include "def.h"
#include "light/Light.h"

namespace SA
{
  class SA_API DirectionalLight : public Light
  {
  public:
    DirectionalLight(
        const glm::vec3 &_direction = Object3D::default_front,
        const Color &_color = 0xffffff,
        const glm::vec3 &_atten);
    DirectionalLight(
        const glm::vec3 &_direction = Object3D::default_front,
        const glm::mat3 &_ads = glm::mat3(glm::vec3(0.0), glm::vec3(1.0), glm::vec3(0.0)),
        const glm::vec3 &_atten = glm::vec3(1.0, 0.0, 0.0));
  };
} // namespace SA
