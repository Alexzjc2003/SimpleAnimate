#include "pch.h"
#include "texture/Texture.h"

using namespace SA;

int Texture::nextId = 1;

Texture::Texture(
    GLenum _target,
    GLsizei _width, GLsizei _height,
    GLenum _wrapS, GLenum _wrapT,
    GLenum _minFilter, GLenum _magFilter,
    GLenum _format, GLenum _type)
    : target(_target),
      width(_width), height(_height),
      wrapS(_wrapS), wrapT(_wrapT),
      minFilter(_minFilter), magFilter(_magFilter),
      format(_format), type(_type),
      id(nextId++)
{
  glGenTextures(1, &texID);
}

