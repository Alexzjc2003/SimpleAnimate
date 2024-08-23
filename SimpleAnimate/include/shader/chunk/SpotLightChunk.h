#pragma once
#include "def.h"
#include "shader/chunk/ShaderChunk.h"

#include "glad/glad.h"

namespace SA
{
  class SA_API SpotLightChunk : public ShaderChunk
  {
  public:
    SpotLightChunk()
        : ShaderChunk(name(), content()) {}
    ~SpotLightChunk() {}

  private:
    static const std::string name()
    {
      return "/SpotLight";
    }
    static const std::string content()
    {
      std::fstream fs;
      fs.open("./static/shader/chunk/SpotLight");
      std::stringstream ss;
      ss << fs.rdbuf();
      fs.close();

      return ss.str();
    }
  };

} // namespace SA
