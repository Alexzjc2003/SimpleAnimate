#include "material/Material.h"
#include <shader/StaticShader.h>
#include <core/Color.h>

#include <string>
#include <glm/glm.hpp>

namespace SA
{
  class SA_API CommonMaterial : public Material
  {
  public:
    CommonMaterial(
        const std::unordered_map<std::string, Texture *> &_maps = {},
        const Color &_color = 0xffffff);

  virtual void updateUniforms();

  private:
    Color color;

    Texture *diffuseMap;

    static StaticShader shader;
  };
} // namespace SA
