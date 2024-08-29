#pragma once

#include "def.h"
#include <glm/glm.hpp>

namespace SA
{
  glm::mat4 SA_API compose(
      const glm::vec3 &translate,
      const glm::quat &rotate,
      const glm::vec3 &scale);

} // namespace SA
