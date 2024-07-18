#pragma once
#include <glad/glad.h>

namespace SA
{
  class Shader
  {
  public:
    void use();

  protected:
    Shader();

    GLuint id;

    GLuint create_shader_from_strings(const char **str, GLsizei num, GLenum type);
    GLuint create_shader_from_file(const char *path, GLenum type);
    void link();
  
  };
} // namespace SA
