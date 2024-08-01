#pragma once
#include "Geometry.h"

namespace SA
{
  class SA_API BoxGeometry : public Geometry
  {
  public:
    BoxGeometry();

    virtual void draw();

  private:
    virtual void setup();
  };
} // namespace SA
