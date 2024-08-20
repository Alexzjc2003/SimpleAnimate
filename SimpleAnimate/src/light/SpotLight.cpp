#include "pch.h"
#include "light/SpotLight.h"

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
	setPosition(_position);
	setDirection(_direction);
	uniform
			.set("position", _position)
			.set("direction", _direction)
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
	setPosition(_position);
	setDirection(_direction);
	uniform
			.set("position", _position)
			.set("direction", _direction)
			.set("cutoff", cutoff);
}