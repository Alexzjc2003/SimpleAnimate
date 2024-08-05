#include "pch.h"
#include "geometry/GeometryVAO.h"

using namespace SA;

GeometryVAO::GeometryVAO()
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBindVertexArray(0);

  count = 0;
  stride = 0;
}

void GeometryVAO::activate() const
{
  glBindVertexArray(VAO);
}

void GeometryVAO::deactivate() const
{
  glBindVertexArray(0);
}

void GeometryVAO::fromAttribs(const std::vector<Attribute> &attrs)
{
  glBindVertexArray(VAO);

  // 1. first make vertex array buffer
  // calculate and update vertex info (stride, offsets)
  size_t _cnt = SIZE_MAX;
  size.clear();
  offset.clear();
  stride = 0;
  for (auto &attr : attrs)
  {
    _cnt = _cnt < attr.cnt ? _cnt : attr.cnt;
    size.push_back(attr.sz);
    stride += attr.sz;
  }
  count = _cnt;

  // 2. construct array buffer
  _arr_buf.reserve(sizeof(attrs));
  _arr_buf.clear();

  // 2.1. calculate offsets
  size_t _offset = 0;
  for (auto &attr : attrs)
  {
    offset.push_back(_offset);
    _offset += attr.sz;
  }

  // 2.2. copy attrs to the array buffer
  for (size_t j = 0; j < count; ++j)
  {
    for (auto &attr : attrs)
    {
      _arr_buf.insert(_arr_buf.end(),
                      attr.getArray().begin() + j * attr.sz,
                      attr.getArray().begin() + j * attr.sz + attr.sz);
    }
  }

  // 3. send to buffer and enable attrs
  glBufferData(GL_ARRAY_BUFFER, _arr_buf.size() * sizeof(float), _arr_buf.data(), GL_STATIC_DRAW);

  for (size_t i = 0; i < attrs.size(); ++i)
  {
    auto &attr = attrs[i];
    if (attr.type < ATTR_TYPE::NR_ATTR_TYPE)
    {
      glEnableVertexAttribArray(attr.type);
      glVertexAttribPointer(attr.type, attr.sz, GL_FLOAT,
                            attr.isNorm ? GL_TRUE : GL_FALSE,
                            stride * sizeof(float), (void*)(offset[i] * sizeof(float)));
    }
  }

  glBindVertexArray(0);
}

void GeometryVAO::setIndices(const std::vector<GLuint> &indices)
{
  glBindVertexArray(VAO);

  _idx_buf.reserve(sizeof(indices));
  _idx_buf.clear();
  for (auto idx : indices)
  {
    if (idx >= count)
    {
      throw "Geometry::Index: Out of range.";
    }
    _idx_buf.push_back(idx);
  }

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, _idx_buf.size() * sizeof(GLuint), _idx_buf.data(), GL_STATIC_DRAW);
}