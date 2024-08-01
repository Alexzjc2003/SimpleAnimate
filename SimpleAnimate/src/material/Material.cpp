#include "pch.h"
#include "material/Material.h"

using namespace SA;

int Material::nextId = 1;

Material::Material() : id(nextId++), pShader(nullptr) {}
// Material::Material(const std::unordered_map<const std::string &, Texture *> _maps = {})
//     : maps(_maps), id(nextId++) {}

void Material::updateUniforms() {}

Texture *Material::getMap(const std::unordered_map<std::string, Texture *> &_maps, const std::string &name)
{
  try
  {
    return _maps.at(name);
  }
  catch (const std::out_of_range &e)
  {
    return nullptr;
  }
}
