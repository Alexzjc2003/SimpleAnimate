#include "pch.h"
#include "texture/Texture.h"

using namespace SA;

int Texture::nextId = 1;

Texture::Texture(
    GLenum _target,
    GLsizei _width = 0, GLsizei _height = 0,
    GLenum _wrapS = GL_CLAMP_TO_EDGE, GLenum _wrapT = GL_CLAMP_TO_EDGE,
    GLenum _minFilter = GL_LINEAR_MIPMAP_LINEAR, GLenum _magFilter = GL_LINEAR,
    GLenum _format = GL_RGBA, GLenum _type = GL_UNSIGNED_BYTE)
    : target(_target),
      width(_width), height(_height),
      wrapS(_wrapS), wrapT(_wrapT),
      minFilter(_minFilter), magFilter(_magFilter),
      format(_format), type(_type),
      id(nextId++)
{
  glGenTextures(1, &texID);
}

