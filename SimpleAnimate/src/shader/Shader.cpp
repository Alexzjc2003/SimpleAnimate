#include "pch.h"
#include "shader/Shader.h"

using namespace SA;

Shader::Shader()
{
  id = glCreateProgram();
}

void Shader::use()
{
  glUseProgram(id);
}

GLuint Shader::create_shader_from_strings(const char **str, GLsizei num, GLenum type)
{
  GLuint _sid;
  int success;
  char info[512];

  _sid = glCreateShader(type);
  glShaderSource(_sid, num, str, NULL);
  glCompileShader(_sid);

  glGetShaderiv(_sid, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(_sid, 512, NULL, info);
    std::cerr << "Shader::create_shader_from_strings: Fail to create shader" << std::endl
              << info << std::endl;
  }

  return _sid;
}

GLuint Shader::create_shader_from_file(const char *path, GLenum type)
{
  const char *_c;
  try
  {
    std::ifstream ifs_shader;
    ifs_shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    ifs_shader.open(path);

    std::stringstream ss_shader;
    ss_shader << ifs_shader.rdbuf();

    _c = ss_shader.str().c_str();
  }
  catch (const std::exception &e)
  {
    std::cerr << "Shader::create_shader_from_file: Fail to load file" << std::endl
              << e.what() << std::endl;
    return 0;
  }

  return create_shader_from_strings(&_c, 1, type);
}

void Shader::link()
{
  glLinkProgram(id);

  int success;
  char info[512];

  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(id, 512, NULL, info);
    std::cerr << "Shader::link: Fail to link program" << std::endl
              << info << std::endl;
  }
}