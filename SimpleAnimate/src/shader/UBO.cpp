#include "pch.h"
#include "shader/UBO.h"

using namespace SA;

UBO::UBO()
{
  glGenBuffers(1, &ubo);
}

void UBO::setup()
{
}

void UBO::activate() const { glBindBuffer(GL_UNIFORM_BUFFER, ubo); }
void UBO::deactivate() const { glBindBuffer(GL_UNIFORM_BUFFER, 0); }