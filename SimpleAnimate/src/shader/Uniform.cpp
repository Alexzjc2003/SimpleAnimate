#include "pch.h"
#include "shader/Uniform.h"

#include <bit>

using namespace SA;

Uniform::Uniform() : ubo() {}

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
  // glBufferSubData(GL_UNIFORM_BUFFER, offset_of<float>(name), 4, &value);

  auto ptr = (float *)glMapBufferRange(GL_UNIFORM_BUFFER, offset_of<float>(name), 4, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
  assert(ptr);
  if (ptr)
    *ptr = value;
  glUnmapBuffer(GL_UNIFORM_BUFFER);

  return *this;
}
template <>
Uniform &Uniform::set<int>(const std::string &name, const int &value)
{
  ubo.activate();
  // glBufferSubData(GL_UNIFORM_BUFFER, offset_of<int>(name), 4, &value);
  
  auto ptr = (int *)glMapBufferRange(GL_UNIFORM_BUFFER, offset_of<int>(name), 4, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
  assert(ptr);
  if (ptr)
    *ptr = value;
  glUnmapBuffer(GL_UNIFORM_BUFFER);
  
  return *this;
}
template <>
Uniform &Uniform::set<bool>(const std::string &name, const bool &value)
{
  ubo.activate();
  // int _val = value;
  // glBufferSubData(GL_UNIFORM_BUFFER, offset_of<bool>(name), 4, &_val);
  
  auto ptr = (int *)glMapBufferRange(GL_UNIFORM_BUFFER, offset_of<bool>(name), 4, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
  assert(ptr);
  if (ptr)
    *ptr = value;
  glUnmapBuffer(GL_UNIFORM_BUFFER);
  
  return *this;
}
template <>
Uniform &Uniform::set<glm::vec2>(const std::string &name, const glm::vec2 &value)
{
  ubo.activate();
  // glBufferSubData(GL_UNIFORM_BUFFER, offset_of<glm::vec2>(name), 8, glm::value_ptr(value));
  
  auto ptr = (glm::vec2 *)glMapBufferRange(GL_UNIFORM_BUFFER, offset_of<glm::vec2>(name), 8, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
  assert(ptr);
  if (ptr)
    *ptr = value;
  glUnmapBuffer(GL_UNIFORM_BUFFER);
  
  
  return *this;
}
template <>
Uniform &Uniform::set<glm::vec3>(const std::string &name, const glm::vec3 &value)
{
  ubo.activate();
  // glBufferSubData(GL_UNIFORM_BUFFER, offset_of<glm::vec3>(name), 12, glm::value_ptr(value));

  auto ptr = (glm::vec3 *)glMapBufferRange(GL_UNIFORM_BUFFER, offset_of<glm::vec3>(name), 12, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
  assert(ptr);
  if (ptr)
    *ptr = value;
  glUnmapBuffer(GL_UNIFORM_BUFFER);
  
  return *this;
}
template <>
Uniform &Uniform::set<glm::vec4>(const std::string &name, const glm::vec4 &value)
{
  ubo.activate();
  // glBufferSubData(GL_UNIFORM_BUFFER, offset_of<glm::vec4>(name), 16, glm::value_ptr(value));

  auto ptr = (glm::vec4 *)glMapBufferRange(GL_UNIFORM_BUFFER, offset_of<glm::vec4>(name), 16, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
  assert(ptr);
  if (ptr)
    *ptr = value;
  glUnmapBuffer(GL_UNIFORM_BUFFER);

  return *this;
}
template <>
Uniform &Uniform::set<glm::mat3>(const std::string &name, const glm::mat3 &value)
{
  ubo.activate();
  // size_t _offset = offset_of<glm::mat3>(name);
  // glBufferSubData(GL_UNIFORM_BUFFER, _offset + 0x00, 12, glm::value_ptr(value[0]));
  // glBufferSubData(GL_UNIFORM_BUFFER, _offset + 0x10, 12, glm::value_ptr(value[1]));
  // glBufferSubData(GL_UNIFORM_BUFFER, _offset + 0x20, 12, glm::value_ptr(value[2]));
  
  auto ptr = (glm::vec4 *)glMapBufferRange(GL_UNIFORM_BUFFER, offset_of<glm::mat3>(name), 48, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
  assert(ptr);
  if (ptr)
  {
    ptr[0] = {value[0], 0.0f};
    ptr[1] = {value[1], 0.0f};
    ptr[2] = {value[2], 0.0f};
  }
  glUnmapBuffer(GL_UNIFORM_BUFFER);

  return *this;
}
template <>
Uniform &Uniform::set<glm::mat4>(const std::string &name, const glm::mat4 &value)
{
  ubo.activate();
  // glBufferSubData(GL_UNIFORM_BUFFER, offset_of<glm::mat4>(name), 64, glm::value_ptr(value));
  
  auto ptr = (glm::mat4 *)glMapBufferRange(GL_UNIFORM_BUFFER, offset_of<glm::mat4>(name), 64, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
  assert(ptr);
  if (ptr)
    *ptr = value;
  glUnmapBuffer(GL_UNIFORM_BUFFER);
  
  return *this;
}
