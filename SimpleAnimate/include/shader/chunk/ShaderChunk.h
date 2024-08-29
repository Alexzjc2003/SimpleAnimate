#pragma once
#include "def.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace SA
{
  class SA_API ShaderChunk
  {
  public:
    std::string content;
    std::string name;
    virtual ~ShaderChunk()
    {
      //glDeleteNamedStringARB(name.length(), name.c_str());
    }

  protected:
    ShaderChunk(const std::string& _name, const std::string& _content)
      : content(_content), name(_name)
    {
      std::cout << name << std::endl
        << content << std::endl;

      
      glNamedStringARB(GL_SHADER_INCLUDE_ARB,
        name.length(), name.c_str(),
        content.length(), content.c_str());
    }
  };

} // namespace SA
