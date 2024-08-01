#include "pch.h"
#include "geometry/PlaneGeometry.h"

using namespace SA;

static const std::vector<float> _plane_pos
{
  -0.5f, -0.5f,  0.0f,  // bottom-left
	 0.5f, -0.5f,  0.0f,  // bottom-right
	 0.5f,  0.5f,  0.0f,  // top-right
	 0.5f,  0.5f,  0.0f,  // top-right
	-0.5f,  0.5f,  0.0f,  // top-left
	-0.5f, -0.5f,  0.0f,  // bottom-left
};

static const std::vector<float> _plane_normal
{
   0.0f,  0.0f,  1.0f,  // bottom-left
	 0.0f,  0.0f,  1.0f,  // bottom-right
	 0.0f,  0.0f,  1.0f,  // top-right
	 0.0f,  0.0f,  1.0f,  // top-right
	 0.0f,  0.0f,  1.0f,  // top-left
	 0.0f,  0.0f,  1.0f,  // bottom-left
};

static const std::vector<float> _plane_uv
{
  1.0f, 0.0f, // bottom-left
	0.0f, 0.0f, // bottom-right
	0.0f, 1.0f, // top-right
	0.0f, 1.0f, // top-right
	1.0f, 1.0f, // top-left
	1.0f, 0.0f, // bottom-left
};

static const std::vector<float> _plane_tangent
{
   1.0f,  0.0f,  0.0f,  // bottom-left
	 1.0f,  0.0f,  0.0f,  // bottom-right
	 1.0f,  0.0f,  0.0f,  // top-right
	 1.0f,  0.0f,  0.0f,  // top-right
	 1.0f,  0.0f,  0.0f,  // top-left
	 1.0f,  0.0f,  0.0f,  // bottom-left
};

static const std::vector<float> _plane_bitangent
{
   0.0f,  1.0f,  0.0f,  // bottom-left
	 0.0f,  1.0f,  0.0f,  // bottom-right
	 0.0f,  1.0f,  0.0f,  // top-right
	 0.0f,  1.0f,  0.0f,  // top-right
	 0.0f,  1.0f,  0.0f,  // top-left
	 0.0f,  1.0f,  0.0f,  // bottom-left
};

PlaneGeometry::PlaneGeometry() 
{
	setup();
}

void PlaneGeometry::setup()
{
  // 1. set attribs
  addAttr(Attribute(ATTR_TYPE::POSITION , _plane_pos      , 3));
  addAttr(Attribute(ATTR_TYPE::NORMAL   , _plane_normal   , 3));
  addAttr(Attribute(ATTR_TYPE::UV       , _plane_uv       , 2));
  addAttr(Attribute(ATTR_TYPE::TANGENT  , _plane_tangent  , 3));
  addAttr(Attribute(ATTR_TYPE::BITANGENT, _plane_bitangent, 3));
  
  // 2. set buffer
  setBuffer();

  // 3. set indices
  auto _indices = std::vector<GLuint>(6);
  for(size_t i = 0; i < _indices.size(); ++i)
    _indices[i] = i;
  setIndices(_indices);
}

void PlaneGeometry::draw()
{
	VAO.activate();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	VAO.deactivate();
}
