#include "pch.h"
#include "Material.h"

using namespace SA;

int Material::nextId = 1;

Material::Material() : id(nextId++)
{
  
}