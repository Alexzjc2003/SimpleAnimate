#pragma once
#include "def.h"
#include "shader/chunk/ShaderChunk.h"

#include <format>

#include "glad/glad.h"

namespace SA
{
  class SA_API SpotLightChunk : public ShaderChunk
  {
  public:
    SpotLightChunk(const int &index)
        : ShaderChunk(content(index), name(index)) {}
    ~SpotLightChunk() {}

  private:
    static const std::string name(const int &index)
    {
      return std::format("/SpotLight_{}", index);
    }
    static const std::string content(const int &index)
    {
      return std::format(
          R"(
(layout (std140) uniform SpotLight_{} 
{{
  SpotLight light;
}};)",
          index);
    }
  };
  
} // namespace SA
