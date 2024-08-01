#pragma once
#include "Geometry.h"

namespace SA
{
  class SA_API PlaneGeometry : public Geometry
  {
  public:
    PlaneGeometry();
    virtual void draw();

  private:
    virtual void setup();
  };
} // namespace SA
