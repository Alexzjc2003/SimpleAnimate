#include "pch.h"
#include "light/DirectionalLight.h"

using namespace SA;

DirectionalLight::DirectionalLight(
		const Color &_color,
		const glm::vec3 &_direction,
		const glm::vec3 &_atten)
		: Light(_color, _atten)
{
	setDir(_direction);
	uniform.set("direction", getDirWorld());
}

DirectionalLight::DirectionalLight(
		const glm::mat3 &_ads,
		const glm::vec3 &_direction,
		const glm::vec3 &_atten)
		: Light(_ads, _atten)
{
	setDir(_direction);
	uniform.set("direction", getDirWorld());
}

void DirectionalLight::updateUniform()
{
	Light::updateUniform();
	uniform.set("direction", getDirWorld());
}
