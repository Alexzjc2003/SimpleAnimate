#pragma once
#include "def.h"

#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

#include <core/State.h>
#include <shader/UBO.h>
#include <glm/gtx/type_trait.hpp>

#include <glad/glad.h>
namespace SA
{
  class SA_API Uniform
  {
  public:
    Uniform();
    Uniform(std::initializer_list<std::pair<const std::string &, const std::variant<float, int, bool, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4>>>);

    UBO ubo;
    template <typename T>
    Uniform &set(const std::string &name, const T &value);

  private:
    std::unordered_map<std::string, size_t> _offset;
    size_t _next_offset = 0;

    size_t align_to(const size_t &_alignment);
    template <typename T>
    size_t offset_of(const std::string &_name);
  };

  template <>
  Uniform &Uniform::set<float>(const std::string &, const float &);
  template <>
  Uniform &Uniform::set<int>(const std::string &, const int &);
  template <>
  Uniform &Uniform::set<bool>(const std::string &, const bool &);
  template <>
  Uniform &Uniform::set<glm::vec2>(const std::string &, const glm::vec2 &);
  template <>
  Uniform &Uniform::set<glm::vec3>(const std::string &, const glm::vec3 &);
  template <>
  Uniform &Uniform::set<glm::vec4>(const std::string &, const glm::vec4 &);
  template <>
  Uniform &Uniform::set<glm::mat3>(const std::string &, const glm::mat3 &);
  template <>
  Uniform &Uniform::set<glm::mat4>(const std::string &, const glm::mat4 &);

  template <>
  size_t Uniform::offset_of<float>(const std::string &);
  template <>
  size_t Uniform::offset_of<int>(const std::string &);
  template <>
  size_t Uniform::offset_of<bool>(const std::string &);
  template <>
  size_t Uniform::offset_of<glm::vec2>(const std::string &);
  template <>
  size_t Uniform::offset_of<glm::vec3>(const std::string &);
  template <>
  size_t Uniform::offset_of<glm::vec4>(const std::string &);
  template <>
  size_t Uniform::offset_of<glm::mat3>(const std::string &);
  template <>
  size_t Uniform::offset_of<glm::mat4>(const std::string &);

} // namespace SA
