#pragma once

#include <def.h>
#include <core/Object3D.h>
#include <core/Color.h>

namespace SA
{
  class SA_API Scene : public Object3D
  {
  public:
    Scene();
    Color color = 0x000000;

    //Scene& add(Object3D*);
    //Scene& remove(Object3D*);

  };
}