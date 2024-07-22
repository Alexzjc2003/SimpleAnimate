#pragma once
#include <unordered_map>
#include <glad/glad.h>

namespace SA
{
  class Texture
  {
  public:
    Texture(
        GLenum _target,
        GLsizei _width = 0, GLsizei _height = 0,
        GLenum _wrapS = GL_CLAMP_TO_EDGE, GLenum _wrapT = GL_CLAMP_TO_EDGE,
        GLenum _minFilter = GL_LINEAR_MIPMAP_LINEAR, GLenum _magFilter = GL_LINEAR,
        GLenum _format = GL_RGBA, GLenum _type = GL_UNSIGNED_BYTE);

    GLsizei width, height;
    GLenum wrapS, wrapT;
    GLenum minFilter, magFilter;
    GLenum format;
    GLenum type;

    int id;

  protected:
    GLenum texID;
    GLenum target;


  private:
    static int nextId;
  };
} // namespace SA
