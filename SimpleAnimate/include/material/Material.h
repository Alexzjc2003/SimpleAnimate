#pragma once
#include <glad/glad.h>

namespace SA
{
  class Material
  {
  public:
    Material();

    int id;

  protected:

    virtual void setup() = 0;

  private:
    static int nextId;
  };
} // namespace SA