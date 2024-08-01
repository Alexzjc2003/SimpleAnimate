#include "pch.h"
#include "geometry/Geometry.h"

using namespace SA;

Geometry::Geometry()
{
  _shape = GEOMETRY::SHAPE::NR_SHAPE;
  // setup();
}

void Geometry::addAttr(const Attribute &attr)
{
  attributes[attr.type] = attr;
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
