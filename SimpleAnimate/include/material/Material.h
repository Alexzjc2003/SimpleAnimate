#pragma once

#include <def.h>
#include <texture/Texture.h>
#include <shader/Shader.h>
#include <glad/glad.h>
#include <unordered_map>

namespace SA
{
  class SA_API Material
  {
  public:
    // std::unordered_map<const std::string &, Texture *> maps;
    int id;
    Shader* pShader;
    virtual void updateUniforms();

  protected:
    Material();
    // Material(const std::unordered_map<const std::string &, Texture *> _maps);
    Texture *getMap(const std::unordered_map<std::string, Texture *> &_maps, const std::string &_name);

  private:
    static int nextId;
  };
} // namespace SA