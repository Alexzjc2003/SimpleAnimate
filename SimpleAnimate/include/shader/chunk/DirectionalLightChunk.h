#pragma once
#include "def.h"
#include "shader/chunk/ShaderChunk.h"

#include <format>
#include <fstream>

#include "glad/glad.h"

namespace SA
{
  class SA_API DirectionalLightChunk : public ShaderChunk
  {
  public:
    DirectionalLightChunk(const int &index) : ShaderChunk(path)
    {
      name = std::format("/DirectionalLight_{}", index);
      std::string content = std::format(files[path], index);
      glNamedStringARB(GL_SHADER_INCLUDE_ARB,
                       name.length(), name.c_str(),
                       content.length(), content.c_str());
    }
    ~DirectionalLightChunk()
    {
      glDeleteNamedStringARB(name.length(), name.c_str());
    }

  private:
    static const std::string path;
  };

  const std::string DirectionalLightChunk::path = "./static/shader/chunk/DirectionalLight";

} // namespace SA
