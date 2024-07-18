#pragma once

#include "shader/Shader.h"

namespace SA
{
  class StaticShader : public Shader
  {
  public:
    StaticShader(const char *_vs_path, const char *_fs_path);
    StaticShader(const char *_vs_path, const char *_fs_path, const char *_gs_path);
  };
} // namespace SA