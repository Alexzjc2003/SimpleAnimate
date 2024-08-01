#pragma once

#include <def.h>
#include <glm/glm.hpp>

namespace SA
{
  class SA_API Color
  {
  private:
    glm::vec<4, unsigned char> _color;

  public:
    Color(const unsigned char &_r,
          const unsigned char &_g,
          const unsigned char &_b,
          const unsigned char &_a = 0xff);
    Color(const unsigned int &_rgba);

    Color &operator=(const unsigned int &_rgba);

    unsigned char &r = _color.r;
    unsigned char &g = _color.g;
    unsigned char &b = _color.b;
    unsigned char &a = _color.a;

  private:
    void fromUint(const unsigned int &_rgba);
  };
} // namespace SA
