#pragma once
#include "def.h"

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace SA
{
  class SA_API ShaderChunk
  {
  public:
    std::string content;

  protected:
    static std::unordered_map<std::string, std::string> files;
    ShaderChunk(const std::string &path)
    {
      if (files.find(path) == files.end())
      {
        std::ifstream ifs;
        ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        ifs.open(path);

        std::stringstream ss;
        ss << ifs.rdbuf();

        files[path] = ss.str();
      }
    }
  };

  std::unordered_map<std::string, std::string> ShaderChunk::files;
} // namespace SA
