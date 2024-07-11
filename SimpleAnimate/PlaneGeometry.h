#pragma once
#include "Geometry.h"

namespace SA
{
  class PlaneGeometry : public Geometry
  {
  public:
    PlaneGeometry();

  private:
    virtual void setup();
  };
} // namespace SA
