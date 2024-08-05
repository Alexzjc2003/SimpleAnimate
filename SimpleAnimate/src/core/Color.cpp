#include "pch.h"
#include "core/Color.h"

using namespace SA;

Color::Color(const unsigned char &_r,
             const unsigned char &_g,
             const unsigned char &_b,
             const unsigned char &_a)
    : _color(_r, _g, _b, _a)
{
}

Color::Color(const unsigned int &_rgba)
{
  fromUint(_rgba);
}

void Color::fromUint(const unsigned int &_rgba)
{
  if (_rgba >> 24)
  {
    // has 'a' byte
    r = 0xff & (_rgba >> 24);
    g = 0xff & (_rgba >> 16);
    b = 0xff & (_rgba >> 8);
    a = 0xff & (_rgba >> 0);
  }
  else
  {
    // no 'a' byte
    r = 0xff & (_rgba >> 16);
    g = 0xff & (_rgba >> 8);
    b = 0xff & (_rgba >> 0);
  }
}