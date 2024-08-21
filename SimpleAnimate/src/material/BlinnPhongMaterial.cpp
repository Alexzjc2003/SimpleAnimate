#include "pch.h"
#include "material/BlinnPhongMaterial.h"

#include "shader/chunk/DirectionalLightChunk.h"
#include "shader/chunk/PointLightChunk.h"
#include "shader/chunk/SpotLightChunk.h"

using namespace SA;

static const std::vector<ShaderChunk>
_chunks()
{
  std::vector<ShaderChunk> chunks;
  for (size_t i = 0; i < 16; i++)
    chunks.push_back(PointLightChunk(i));
  for (size_t i = 0; i < 16; i++)
    chunks.push_back(DirectionalLightChunk(i));
  for (size_t i = 0; i < 4; i++)
    chunks.push_back(SpotLightChunk(i));
  return chunks;
}

IncludeShader *BlinnPhongMaterial::shader = nullptr;

BlinnPhongMaterial::BlinnPhongMaterial(
    const std::unordered_map<std::string, Texture *> &_maps,
    const float &_shininess)
    : shiniess(_shininess)
{
  diffuseMap = getMap(_maps, "diffuse");
  specularMap = getMap(_maps, "specular");
  shader = new IncludeShader(
      "./static/shader/include/blinn_phong/.vert",
      "./static/shader/include/blinn_phong/.frag",
      _chunks());
  pShader = BlinnPhongMaterial::shader;
}

void BlinnPhongMaterial::updateUniforms()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(diffuseMap->target, diffuseMap->texID);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(specularMap->target, specularMap->texID);

  pShader->use()
      .set("shininess", shiniess)
      .set("diffuseMap", 0)
      .set("specularMap", 1);
}