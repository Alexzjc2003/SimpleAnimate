#pragma once
#include "def.h"
#include "shader/chunk/ShaderChunk.h"

#include <format>

#include "glad/glad.h"

namespace SA
{
  class SA_API DirectionalLightChunk : public ShaderChunk
  {
  public:
    DirectionalLightChunk(const int &index)
        : ShaderChunk(content(index), name(index)) {}
    ~DirectionalLightChunk() {}

  private:
    static const std::string name(const int &index)
    {
      return std::format("/DirectionalLight_{}", index);
    }
    static const std::string content(const int &index)
    {
      return std::format(
          R"(
(layout (std140) uniform DirectionalLight_{} 
{{
  DirectionalLight light;
}};)",
          index);
    }
  };

} // namespace SA
