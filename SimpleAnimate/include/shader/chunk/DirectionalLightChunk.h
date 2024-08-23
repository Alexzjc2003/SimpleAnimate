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
    DirectionalLightChunk()
        : ShaderChunk(name(), content()) {}
    ~DirectionalLightChunk() {};

  private:
    static const std::string name()
    {
      return "/DirectionalLight";
    }
    static const std::string content()
    {
      std::fstream fs;
      fs.open("./static/shader/chunk/DirectionalLight");
      std::stringstream ss;
      ss << fs.rdbuf();
      fs.close();

      return ss.str();
    }
  };

} // namespace SA
