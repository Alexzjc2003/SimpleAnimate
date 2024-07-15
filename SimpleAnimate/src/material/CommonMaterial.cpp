#include "pch.h"
#include "CommonMaterial.h"

using namespace SA;

// CommonMaterial::CommonMaterial() : color(0xff)
// {
// }

CommonMaterial::CommonMaterial(const char *_filename)
{
  textureId = loadTextureFromFile(_filename);
}

CommonMaterial::CommonMaterial(const glm::vec3 &_color) : color(_color)
{
  textureId = loadTextureFromColor(_color);
}