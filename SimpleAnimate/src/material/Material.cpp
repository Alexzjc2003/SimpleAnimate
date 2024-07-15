#include "pch.h"
#include "material/Material.h"

using namespace SA;

int Material::nextId = 1;

Material::Material() : id(nextId++)
{
}

GLuint Material::loadTextureFromFile(const char *filename)
{
  if (!_loaded_textures[filename])
  {
    GLuint _t;
    glGenTextures(1, &_t);
    glBindTexture(GL_TEXTURE_2D, _t);

    int width, height, nrChannels;
    unsigned char *data;

    const char *ext = strrchr(filename, '.');
    if (strcmp(ext, ".jpg"))
      stbi_set_flip_vertically_on_load(true);

    data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if (!data)
      throw "Material::loadTextureFromFile: Fail to load texture.";

    GLenum format = GL_RGB;
    if (nrChannels == 1)
      format = GL_RED;
    else if (nrChannels == 3)
      format = GL_RGB;
    else if (nrChannels == 4)
      format = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    _loaded_textures[filename] = _t;
  }

  return _loaded_textures[filename];
}

GLuint Material::loadTextureFromColor(const glm::vec3 &_color)
{
  GLuint _t;
  glGenTextures(1, &_t);
  glBindTexture(GL_TEXTURE_2D, _t);

  char data[3];
  data[0] = (unsigned char)_color.r;
  data[1] = (unsigned char)_color.g;
  data[2] = (unsigned char)_color.b;

  glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return _t;
}