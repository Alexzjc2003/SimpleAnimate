#pragma once
#include "def.h"
#include "shader/chunk/ShaderChunk.h"

#include <format>

#include "glad/glad.h"

namespace SA
{
  class SA_API PointLightChunk : public ShaderChunk
  {
  public:
    PointLightChunk(const int &index)
        : ShaderChunk(content(index), name(index)) {}
    ~PointLightChunk() {}

  private:
    static const std::string name(const int &index)
    {
      return std::format("/PointLight_{}", index);
    }
    static const std::string content(const int &index)
    {
      return std::format(
          R"(
(layout (std140) uniform PointLight_{} 
{{
  PointLight light;
}};)",
          index);
    }
  };

} // namespace SA
