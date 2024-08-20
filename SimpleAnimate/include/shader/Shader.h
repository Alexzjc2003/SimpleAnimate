#pragma once

#include <def.h>
#include <glad/glad.h>
#include <shader/UBO.h>

namespace SA
{
  class SA_API Shader
  {
  public:
    const Shader &use() const;
    template <typename T>
    const Shader &set(const std::string &uName, const T &value) const;
    const Shader &bindUBO(const std::string &uName, const UBO &ubo) const;


  protected:
    Shader();

    GLuint id;

    GLuint load_from_strings(const char **str, GLsizei num, GLenum type);
    GLuint load_from_file(const char *path, GLenum type);
    void link();
    void compile(GLuint sid);
  };
} // namespace SA
