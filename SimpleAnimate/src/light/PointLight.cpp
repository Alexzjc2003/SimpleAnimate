#include "pch.h"
#include "light/PointLight.h"

using namespace SA;

PointLight::PointLight(
		const Color &_color,
		const glm::vec3 &_position,
		const glm::vec3 &_atten)
		: Light(_color, _atten)
{
	setPos(_position);
	uniform.set("position", getPosWorld());
}

PointLight::PointLight(
		const glm::mat3 &_ads,
		const glm::vec3 &_position,
		const glm::vec3 &_atten)
		: Light(_ads, _atten)
{
	setPos(_position);
	uniform.set("position", getPosWorld());
}

void PointLight::updateUniform()
{
	Light::updateUniform();
	uniform.set("position", getPosWorld());
}