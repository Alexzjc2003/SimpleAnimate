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
    PointLightChunk()
        : ShaderChunk(name(), content()) {}
    ~PointLightChunk() {}

  private:
    static const std::string name()
    {
      return "/PointLight";
    }
    static const std::string content()
    {
      std::fstream fs;
      fs.open("./static/shader/chunk/PointLight");
      std::stringstream ss;
      ss << fs.rdbuf();
      fs.close();

      return ss.str();
    }
  };

} // namespace SA
