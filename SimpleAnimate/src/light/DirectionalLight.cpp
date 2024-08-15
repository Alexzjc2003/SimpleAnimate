#include "pch.h"
#include "light/DirectionalLight.h"

using namespace SA;

DirectionalLight::DirectionalLight(
    const glm::vec3 &_direction,
    const Color &_color,
    const glm::vec3 &_atten) : Light(_color, _atten)
{
  setDirection(_direction);
}

DirectionalLight::DirectionalLight(
    const glm::vec3 &_direction,
    const glm::mat3 &_ads,
    const glm::vec3 &_atten) : Light(_ads, _atten)
{
  setDirection(_direction);
}


