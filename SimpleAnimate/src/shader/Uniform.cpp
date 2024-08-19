#include "pch.h"
#include "shader/Uniform.h"

#include <bit>

using namespace SA;

Uniform::Uniform() : ubo() {}
Uniform::Uniform(std::initializer_list<std::pair<const std::string &, const std::variant<float, int, bool, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4>>> _l) : ubo()
{
  for (auto &_p : _l)
  {
    set(_p.first, _p.second);
  }
}

size_t Uniform::align_to(const size_t &_alignment)
{
  while (_next_offset % _alignment)
    ++_next_offset;

  return _next_offset;
}

template <>
size_t Uniform::offset_of<float>(const std::string &_name)
{
  if (_offset.find(_name) == _offset.end())
  {
    _offset[_name] = align_to(4);
    _next_offset += 4;
  }
  return _offset[_name];
}
template <>
size_t Uniform::offset_of<int>(const std::string &_name)
{
  if (_offset.find(_name) == _offset.end())
  {
    _offset[_name] = align_to(4);
    _next_offset += 4;
  }

  return _offset[_name];
}
template <>
size_t Uniform::offset_of<bool>(const std::string &_name)
{
  if (_offset.find(_name) == _offset.end())
  {
    _offset[_name] = align_to(4);
    _next_offset += 4;
  }

  return _offset[_name];
}
template <>
size_t Uniform::offset_of<glm::vec2>(const std::string &_name)
{
  if (_offset.find(_name) == _offset.end())
  {
    _offset[_name] = align_to(8);
    _next_offset += 8;
  }

  return _offset[_name];
}
template <>
size_t Uniform::offset_of<glm::vec3>(const std::string &_name)
{
  if (_offset.find(_name) == _offset.end())
  {
    _offset[_name] = align_to(16);
    _next_offset += 12;
  }

  return _offset[_name];
}
template <>
size_t Uniform::offset_of<glm::vec4>(const std::string &_name)
{
  if (_offset.find(_name) == _offset.end())
  {
    _offset[_name] = align_to(16);
    _next_offset += 16;
  }

  return _offset[_name];
}
template <>
size_t Uniform::offset_of<glm::mat3>(const std::string &_name)
{
  if (_offset.find(_name) == _offset.end())
  {
    _offset[_name] = align_to(16);
    _next_offset += 48;
  }
  return _offset[_name];
}
template <>
size_t Uniform::offset_of<glm::mat4>(const std::string &_name)
{
  if (_offset.find(_name) == _offset.end())
  {
    _offset[_name] = align_to(16);
    _next_offset += 64;
  }
  return _offset[_name];
}

template <>
Uniform &Uniform::set<float>(const std::string &name, const float &value)
{
  ubo.activate();
  glBufferSubData(GL_UNIFORM_BUFFER, offset_of<float>(name), 4, &value);
}
template <>
Uniform &Uniform::set<int>(const std::string &name, const int &value)
{
  ubo.activate();
  glBufferSubData(GL_UNIFORM_BUFFER, offset_of<int>(name), 4, &value);
}
template <>
Uniform &Uniform::set<bool>(const std::string &name, const bool &value)
{
  ubo.activate();
  int _val = value;
  glBufferSubData(GL_UNIFORM_BUFFER, offset_of<bool>(name), 4, &_val);
}
template <>
Uniform &Uniform::set<glm::vec2>(const std::string &name, const glm::vec2 &value)
{
  ubo.activate();
  glBufferSubData(GL_UNIFORM_BUFFER, offset_of<glm::vec2>(name), 8, glm::value_ptr(value));
}
template <>
Uniform &Uniform::set<glm::vec3>(const std::string &name, const glm::vec3 &value)
{
  ubo.activate();
  glBufferSubData(GL_UNIFORM_BUFFER, offset_of<glm::vec3>(name), 12, glm::value_ptr(value));
}
template <>
Uniform &Uniform::set<glm::vec4>(const std::string &name, const glm::vec4 &value)
{
  ubo.activate();
  glBufferSubData(GL_UNIFORM_BUFFER, offset_of<glm::vec4>(name), 16, glm::value_ptr(value));
}
template <>
Uniform &Uniform::set<glm::mat3>(const std::string &name, const glm::mat3 &value)
{
  ubo.activate();
  size_t _offset = offset_of<glm::mat3>(name);
  glBufferSubData(GL_UNIFORM_BUFFER, _offset + 0x00, 12, glm::value_ptr(value[0]));
  glBufferSubData(GL_UNIFORM_BUFFER, _offset + 0x10, 12, glm::value_ptr(value[1]));
  glBufferSubData(GL_UNIFORM_BUFFER, _offset + 0x20, 12, glm::value_ptr(value[2]));
}
template <>
Uniform &Uniform::set<glm::mat4>(const std::string &name, const glm::mat4 &value)
{
  ubo.activate();
  glBufferSubData(GL_UNIFORM_BUFFER, offset_of<glm::mat4>(name), 64, glm::value_ptr(value));
}
