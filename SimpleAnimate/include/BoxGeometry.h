#pragma once
#include "Geometry.h"

namespace SA
{
  class BoxGeometry : public Geometry
  {
  public:
    BoxGeometry();

  private:
    virtual void setup();
  };
} // namespace SA
