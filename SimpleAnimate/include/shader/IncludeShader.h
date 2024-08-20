/*
 * This shader will process the include directives
 * before compiling.
 */

#pragma once

#include "def.h"

#include "shader/Shader.h"
#include "shader/chunk/ShaderChunk.h"
namespace SA
{
  class SA_API IncludeShader : public Shader
  {
  public:
    IncludeShader(
        const char *_vs_path,
        const char *_fs_path,
        const std::vector<ShaderChunk> &_chunks);
    // IncludeShader(const char *_vs_path, const char *_fs_path);

  private:
    void compile(GLuint sid, GLsizei _count, const char **_strings, const GLint *_lengths);
  };
} // namespace SA
