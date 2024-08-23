#include "pch.h"
#include "shader/IncludeShader.h"

using namespace SA;

IncludeShader::IncludeShader(
  const char* _vs_path, const char* _fs_path,
  const std::vector<ShaderChunk>& _chunks)
{
  // process chunks
  GLsizei count = _chunks.size();
  const char** const strings = new const char* [count];
  GLint* const lengths = new GLint[count];
  for (int i = 0; i < count; i++)
  {
    strings[i] = _chunks[i].name.c_str();
    lengths[i] = _chunks[i].name.length();
  }

  std::vector<GLuint> _sid;
  if (*_vs_path)
  {
    _sid.push_back(load_from_file(_vs_path, GL_VERTEX_SHADER));
    compile(_sid.back(), count, strings, lengths);
    glAttachShader(id, _sid.back());
  }
  if (*_fs_path)
  {
    _sid.push_back(load_from_file(_fs_path, GL_FRAGMENT_SHADER));
    compile(_sid.back(), count, strings, lengths);
    glAttachShader(id, _sid.back());
  }

  link();

  for (auto _id : _sid)
    glDeleteShader(_id);
  delete[] strings;
  delete[] lengths;
}

void IncludeShader::compile(GLuint sid, GLsizei _count, const char** _strings, const GLint* _lengths)
{
  int success;
  char info[512];

  //for (auto i = 0; i < _count; ++i)
  //{
  //  if (glIsNamedStringARB(_lengths[i], _strings[i]))
  //    printf("%d, %s\n", _lengths[i], _strings[i]);
  //}

  glCompileShaderIncludeARB(sid, _count, _strings, _lengths);

  glGetShaderiv(sid, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(sid, 512, NULL, info);
    std::cerr << "Shader::load_from_strings: Fail to create shader" << std::endl
      << info << std::endl;
  }
}