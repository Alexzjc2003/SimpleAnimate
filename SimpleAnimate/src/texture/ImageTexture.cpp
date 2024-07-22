#include "pch.h"
#include "texture/ImageTexture.h"

using namespace SA;

ImageTexture::ImageTexture(
    const char *_path,
    GLenum _wrapS = GL_CLAMP_TO_EDGE, GLenum _wrapT = GL_CLAMP_TO_EDGE,
    GLenum _minFilter = GL_LINEAR_MIPMAP_LINEAR, GLenum _magFilter = GL_LINEAR,
    GLenum _type = GL_UNSIGNED_BYTE)
    : Texture(GL_TEXTURE_2D,
              0, 0,
              _wrapS, _wrapT,
              _minFilter, _magFilter,
              GL_RGB, _type),
      path(_path)
{
  glBindTexture(target, texID);

  int channel;
  unsigned char *data;

  stbi_set_flip_vertically_on_load(true);

  data = stbi_load(_path, &width, &height, &channel, 0);
  if (!data)
    throw "Texture: Fail to load texture from file.";

  switch (channel)
  {
  case 1:
    format = GL_RED;
    break;
  case 2:
    format = GL_RG;
    break;
  case 3:
    format = GL_RGB;
    break;
  case 4:
    format = GL_RGBA;
    break;
  }

  glTexImage2D(target, 0, GL_SRGB,
               width, height, 0, format, type, data);
  glGenerateMipmap(target);

  glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
  glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
  glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);

  stbi_image_free(data);
}