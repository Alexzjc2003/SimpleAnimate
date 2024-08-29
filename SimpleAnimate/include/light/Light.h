#pragma once
#include "def.h"
#include "core/Object3D.h"
#include "core/Color.h"
#include "core/State.h"
#include "shader/Uniform.h"

namespace SA
{
	class SA_API Light : public Object3D
	{
	public:
		Light(const Color& _color,
			const glm::vec3& _atten = glm::vec3(1.0, 0.0, 0.0));
		Light(const glm::mat3& _ads,
			const glm::vec3& _atten = glm::vec3(1.0, 0.0, 0.0));
		virtual ~Light() = default;

		glm::vec3 atten;
		glm::mat3 ads;

		glm::vec3& ambient = ads[0];
		glm::vec3& diffuse = ads[1];
		glm::vec3& specular = ads[2];

		State state = State();
		Uniform uniform;

		virtual void updateUniform();

	};
} // namespace SA
