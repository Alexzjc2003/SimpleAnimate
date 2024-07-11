#pragma once

#include <glad/glad.h>

#include <Attribute.h>

namespace SA
{

  class GeometryVAO
  {
  public:
    GLuint VAO, VBO, EBO;
    size_t count;
    size_t stride;
    std::vector<size_t> size;
    std::vector<size_t> offset;
    std::vector<ATTR_TYPE> type;

    GeometryVAO();
    void active() const;
    void deactive() const;

    void fromAttribs(const std::vector<Attribute> &attrs);
    void setIndices(const std::vector<GLuint> &indices);

  private:
    std::vector<float> _arr_buf;
    std::vector<GLuint> _idx_buf;
  };
}
