#include <material/Material.h>
#include <glm/glm.hpp>

namespace SA
{
  class CommonMaterial : public Material
  {

  public:
    // CommonMaterial();
    CommonMaterial(const glm::vec3 &_color);
    CommonMaterial(const char *_filename);

    glm::vec3 color;
    GLuint textureId;

  private:
    virtual void setup() { type = MATERIAL::TYPE::COMMON; }
  };
} // namespace SA
