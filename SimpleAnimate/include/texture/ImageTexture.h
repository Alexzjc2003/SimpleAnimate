#pragma once
#include "texture/Texture.h"

#include <string>

namespace SA
{
  class ImageTexture : public Texture
  {
  public:
    ImageTexture(
        const char *_path,
        GLenum _wrapS = GL_CLAMP_TO_EDGE, GLenum _wrapT = GL_CLAMP_TO_EDGE,
        GLenum _minFilter = GL_LINEAR_MIPMAP_LINEAR, GLenum _magFilter = GL_LINEAR,
        GLenum _type = GL_UNSIGNED_BYTE);

    std::string path;

  private:
  };
} // namespace SA
