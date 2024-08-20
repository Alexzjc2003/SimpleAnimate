#pragma once

#include "material/Material.h"
#include "shader/IncludeShader.h"

#include <string>

namespace SA
{
  class BlinnPhongMaterial : public Material
  {
  public:
    BlinnPhongMaterial(
        const std::unordered_map<std::string, Texture *> &_maps,
        const float &_shininess);

    virtual void updateUniforms();

  private:
    float shiniess;
    Texture *diffuseMap;
    Texture *specularMap;

    static IncludeShader shader;
  };
} // namespace SA