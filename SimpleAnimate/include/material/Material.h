#pragma once
#include <glad/glad.h>
#include <unordered_map>

namespace SA
{
  namespace MATERIAL
  {
    enum TYPE : size_t
    {
      COMMON,
      PHONG,
      DEPTH,
      SHADOW,
      NR_TYPE
    };

  } // namespace MATERIAL
  class Material
  {
  public:
    Material();

    int id;
    MATERIAL::TYPE type = NR_TYPE;

  protected:
    virtual void setup() = 0;
    GLuint loadTextureFromFile(const char *_path);
    GLuint loadTextureFromColor(const glm::vec3 &_color);

    std::unordered_map<const char *, GLuint> _loaded_textures;

  private:
    static int nextId;
  };
} // namespace SA