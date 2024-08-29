#include "pch.h"
#include "light/SpotLight.h"

#include "util/Logger.h"

using namespace SA;

SpotLight::SpotLight(
		const Color &_color,
		const glm::vec3 &_position,
		const glm::vec3 &_direction,
		const float &_cutoff_outer, const float &_cutoff_inner,
		const glm::vec3 &_atten)
		: Light(_color, _atten),
			cutoff(
					glm::cos(glm::radians(_cutoff_outer)),
					glm::cos(glm::radians(_cutoff_inner)))
{
	setPos(_position);
	setDir(_direction);
	uniform
			.set("position", getPosWorld())
			.set("direction", getDirWorld())
			.set("cutoff", cutoff);
}

SpotLight::SpotLight(
		const glm::mat3 &_ads,
		const glm::vec3 &_position,
		const glm::vec3 &_direction,
		const float &_cutoff_outer, const float &_cutoff_inner,
		const glm::vec3 &_atten)
		: Light(_ads, _atten),
			cutoff(
					glm::cos(glm::radians(_cutoff_outer)),
					glm::cos(glm::radians(_cutoff_inner)))
{
	setPos(_position);
	setDir(_direction);
	uniform
			.set("position", getPosWorld())
			.set("direction", getDirWorld())
			.set("cutoff", cutoff);
}

void SpotLight::updateUniform()
{
	Light::updateUniform();
	uniform
			.set("position", getPosWorld())
			.set("direction", getDirWorld())
			.set("cutoff", cutoff);
}