#include "pch.h"
#include "Geometry.h"

using namespace SA;

Geometry::Geometry()
{
  _shape = GEOMETRY::SHAPE::NR_SHAPE;
  setup();
}

void Geometry::setAttr(const ATTR_TYPE t, const Attribute &attr)
{
  this->attributes[t] = attr;
  _buf_needs_update = true;
}

void Geometry::setIndices(const std::vector<GLuint> &indices)
{
  VAO.setIndices(indices);
}

void Geometry::setBuffer()
{
  if (!_buf_needs_update)
    return;
  _buf_needs_update = false;

  auto attrs = std::vector<Attribute>();
  for (auto &attr : attributes)
  {
    if (attr.cnt == 0)
      continue;
    attrs.push_back(attr);
  }

  VAO.fromAttribs(attrs);
}
