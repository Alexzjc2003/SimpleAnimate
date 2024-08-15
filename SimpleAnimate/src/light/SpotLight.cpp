#include "pch.h"
#include "light/SpotLight.h"

using namespace SA;

SpotLight::SpotLight(
    const glm::vec3 &_position,
    const glm::vec3 &_direction,
    const float &_cutoff_outer, const float &_cutoff_inner,
    const Color &_color,
    const glm::vec3 &_atten)
    : Light(_color, _atten),
      cutoff(
          glm::cos(glm::radians(_cutoff_inner)),
          glm::cos(glm::radians(_cutoff_outer)))
{
  setPosition(_position);
  setDirection(_direction);
}

SpotLight::SpotLight(
    const glm::vec3 &_position,
    const glm::vec3 &_direction,
    const float &_cutoff_outer, const float &_cutoff_inner,
    const glm::mat3 &_ads,
    const glm::vec3 &_atten)
    : Light(_ads, _atten),
      cutoff(
          glm::cos(glm::radians(_cutoff_inner)),
          glm::cos(glm::radians(_cutoff_outer)))
{
  setPosition(_position);
  setDirection(_direction);
}