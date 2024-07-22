#include "material/Material.h"
#include <Color.h>

#include <string>
#include <glm/glm.hpp>

namespace SA
{
  class CommonMaterial : public Material
  {
  public:
    CommonMaterial(
        const std::unordered_map<std::string, Texture *> &_maps = {},
        const Color &_color = 0xffffff);

  private:
    Color color;

    Texture *diffuseMap;

    
  };
} // namespace SA
