#pragma once

#include <glad/glad.h>

#include <geometry/Attribute.h>

namespace SA
{

  class SA_API GeometryVAO
  {
  public:
    GLuint VAO, VBO, EBO;
    size_t count;   // count of primitives
    size_t stride;  // stride of each primitive
    std::vector<size_t> size;     // size of each attr
    std::vector<size_t> offset;   // offset of each attr
    std::vector<ATTR_TYPE> type;  // type of each attr

    GeometryVAO();
    void activate() const;
    void deactivate() const;

    void fromAttribs(const std::vector<Attribute> &attrs);
    void setIndices(const std::vector<GLuint> &indices);

  private:
    std::vector<float> _arr_buf;
    std::vector<GLuint> _idx_buf;
  };
}
