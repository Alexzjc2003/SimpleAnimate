#pragma once
#include "Geometry.h"

namespace SA
{
  class PlaneGeometry : public Geometry
  {
  public:
    PlaneGeometry();
    virtual void draw();

  private:
    virtual void setup();
  };
} // namespace SA
