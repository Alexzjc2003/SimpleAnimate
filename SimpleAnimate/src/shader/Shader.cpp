#include "pch.h"
#include "shader/Shader.h"

using namespace SA;

Shader::Shader()
{
  id = glCreateProgram();
}

const Shader &Shader::use() const
{
  glUseProgram(id);
  return *this;
}

GLuint Shader::load_from_strings(const char **str, GLsizei num, GLenum type)
{
  GLuint _sid;
  _sid = glCreateShader(type);
  glShaderSource(_sid, num, str, NULL);

  return _sid;
}

GLuint Shader::load_from_file(const char *path, GLenum type)
{
  try
  {
    std::ifstream ifs_shader;
    ifs_shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    ifs_shader.open(path);

    std::stringstream ss_shader;
    ss_shader << ifs_shader.rdbuf();

    std::string _s = ss_shader.str();
    const char *_c = _s.c_str();
    return load_from_strings(&_c, 1, type);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Shader::load_from_file: Fail to load file" << std::endl
              << e.what() << std::endl;
    return 0;
  }
  return 0;
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

void Shader::compile(GLuint sid)
{
  int success;
  char info[512];

  glCompileShader(sid);

  glGetShaderiv(sid, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(sid, 512, NULL, info);
    std::cerr << "Shader::load_from_strings: Fail to create shader" << std::endl
              << info << std::endl;
  }
}

template <typename T>
const Shader &Shader::set(const std::string &uName, const T &value) const
{
  throw "Shader::set: Value type not supported";
  return *this;
}

template <>
const Shader &Shader::set<GLboolean>(const std::string &uName, const GLboolean &value) const
{
  auto uloc = glGetUniformLocation(this->id, uName.c_str());
  glUniform1i(uloc, (int)value);
  return *this;
}

template <>
const Shader &Shader::set<GLint>(const std::string &uName, const GLint &value) const
{
  auto uloc = glGetUniformLocation(this->id, uName.c_str());
  glUniform1i(uloc, value);
  return *this;
}

template <>
const Shader &Shader::set<GLfloat>(const std::string &uName, const GLfloat &value) const
{
  auto uloc = glGetUniformLocation(this->id, uName.c_str());
  glUniform1f(uloc, value);
  return *this;
}

template <>
const Shader &Shader::set<glm::mat4>(const std::string &uName, const glm::mat4 &value) const
{
  auto uloc = glGetUniformLocation(this->id, uName.c_str());
  glUniformMatrix4fv(uloc, 1, false, glm::value_ptr(value));
  return *this;
}

template <>
const Shader &Shader::set<glm::vec3>(const std::string &uName, const glm::vec3 &value) const
{
  auto uloc = glGetUniformLocation(this->id, uName.c_str());
  glUniform3fv(uloc, 1, glm::value_ptr(value));
  return *this;
}
template <>
const Shader &Shader::set<glm::vec2>(const std::string &uName, const glm::vec2 &value) const
{
  auto uloc = glGetUniformLocation(this->id, uName.c_str());
  glUniform3fv(uloc, 1, glm::value_ptr(value));
  return *this;
}
