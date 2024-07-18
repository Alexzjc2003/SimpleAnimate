#include "pch.h"
#include "shader/StaticShader.h"

using namespace SA;

StaticShader::StaticShader(
    const char *_vs_path,
    const char *_fs_path)
{
  std::vector<GLuint> _sid;
  if (*_vs_path)
  {
    _sid.push_back(create_shader_from_file(_vs_path, GL_VERTEX_SHADER));
    glAttachShader(id, _sid.back());
  }
  if (*_fs_path)
  {
    _sid.push_back(create_shader_from_file(_fs_path, GL_FRAGMENT_SHADER));
    glAttachShader(id, _sid.back());
  }

  link();
  for (auto _id : _sid)
    glDeleteShader(_id);
}

StaticShader::StaticShader(
    const char *_vs_path,
    const char *_fs_path,
    const char *_gs_path)
{
  std::vector<GLuint> _sid;
  if (*_vs_path)
  {
    _sid.push_back(create_shader_from_file(_vs_path, GL_VERTEX_SHADER));
    glAttachShader(id, _sid.back());
  }
  if (*_fs_path)
  {
    _sid.push_back(create_shader_from_file(_fs_path, GL_FRAGMENT_SHADER));
    glAttachShader(id, _sid.back());
  }
  if (*_gs_path)
  {
    _sid.push_back(create_shader_from_file(_gs_path, GL_GEOMETRY_SHADER));
    glAttachShader(id, _sid.back());
  }

  link();
  for (auto _id : _sid)
    glDeleteShader(_id);
}
