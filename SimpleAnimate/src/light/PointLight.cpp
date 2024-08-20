#include "pch.h"
#include "light/PointLight.h"

using namespace SA;

PointLight::PointLight(const glm::vec3 &_position,
                       const Color &_color,
                       const glm::vec3 &_atten)
    : Light(_color, _atten)
{
  setPosition(_position);
  uniform.set("position", _position);
}

PointLight::PointLight(const glm::vec3 &_position,
                       const glm::mat3 &_ads,
                       const glm::vec3 &_atten)
    : Light(_ads, _atten)
{
  setPosition(_position);
  uniform.set("position", _position);
}