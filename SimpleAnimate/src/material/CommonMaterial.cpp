#include "pch.h"
#include "material/CommonMaterial.h"

using namespace SA;

StaticShader CommonMaterial::shader = StaticShader("./static/commom/.vert", "./static/common/.frag");

CommonMaterial::CommonMaterial(
    const std::unordered_map<std::string, Texture *> &_maps = {},
    const Color &_color = 0xffffff)
    : //  Material(_maps),
      color(_color)
{
  diffuseMap = getMap(_maps, "diffuse");
  pShader = &shader;
}

void CommonMaterial::updateUniforms()
{
  shader.use()
      .set("uDiffuse", diffuseMap->id);
}
