#pragma once

#include "def.h"

#include <glad/glad.h>

namespace SA
{
  class SA_API UBO
  {

  public:
    UBO();
    void setup();

    void activate() const;
    void deactivate() const;

  private:
    GLuint ubo;
  };
} // namespace SA
