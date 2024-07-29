#pragma once
#include "Geometry.h"

namespace SA
{
  class BoxGeometry : public Geometry
  {
  public:
    BoxGeometry();

    virtual void draw();

  private:
    virtual void setup();
  };
} // namespace SA
