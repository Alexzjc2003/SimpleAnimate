#include "pch.h"
#include "BoxGeometry.h"

using namespace SA;

static std::vector<float> _box_pos
{
	// back face
	-0.5f, -0.5f, -0.5f,  // bottom-left
	 0.5f,  0.5f, -0.5f,  // top-right
	 0.5f, -0.5f, -0.5f,  // bottom-right
	 0.5f,  0.5f, -0.5f,  // top-right
	-0.5f, -0.5f, -0.5f,  // bottom-left
	-0.5f,  0.5f, -0.5f,  // top-left
	// front face
	-0.5f, -0.5f,  0.5f,  // bottom-left
	 0.5f, -0.5f,  0.5f,  // bottom-right
	 0.5f,  0.5f,  0.5f,  // top-right
	 0.5f,  0.5f,  0.5f,  // top-right
	-0.5f,  0.5f,  0.5f,  // top-left
	-0.5f, -0.5f,  0.5f,  // bottom-left
	// left face
	-0.5f,  0.5f,  0.5f,  // top-right
	-0.5f,  0.5f, -0.5f,  // top-left
	-0.5f, -0.5f, -0.5f,  // bottom-left
	-0.5f, -0.5f, -0.5f,  // bottom-left
	-0.5f, -0.5f,  0.5f,  // bottom-right
	-0.5f,  0.5f,  0.5f,  // top-right
	// right face
	 0.5f,  0.5f,  0.5f,  // top-left
	 0.5f, -0.5f, -0.5f,  // bottom-right
	 0.5f,  0.5f, -0.5f,  // top-right
	 0.5f, -0.5f, -0.5f,  // bottom-right
	 0.5f,  0.5f,  0.5f,  // top-left
	 0.5f, -0.5f,  0.5f,  // bottom-left
	// bottom face
	-0.5f, -0.5f, -0.5f,  // top-right
	 0.5f, -0.5f, -0.5f,  // top-left
	 0.5f, -0.5f,  0.5f,  // bottom-left
	 0.5f, -0.5f,  0.5f,  // bottom-left
	-0.5f, -0.5f,  0.5f,  // bottom-right
	-0.5f, -0.5f, -0.5f,  // top-right
	// top face
	-0.5f,  0.5f, -0.5f,  // top-left
	 0.5f,  0.5f,  0.5f,  // bottom-right
	 0.5f,  0.5f, -0.5f,  // top-right
	 0.5f,  0.5f,  0.5f,  // bottom-right
	-0.5f,  0.5f, -0.5f,  // top-left
	-0.5f,  0.5f,  0.5f,  // bottom-left
};

static std::vector<float> _box_normal
{
	// back face
	 0.0f,  0.0f, -1.0f,  // bottom-left
	 0.0f,  0.0f, -1.0f,  // top-right
	 0.0f,  0.0f, -1.0f,  // bottom-right
	 0.0f,  0.0f, -1.0f,  // top-right
	 0.0f,  0.0f, -1.0f,  // bottom-left
	 0.0f,  0.0f, -1.0f,  // top-left
	// front face
	 0.0f,  0.0f,  1.0f,  // bottom-left
	 0.0f,  0.0f,  1.0f,  // bottom-right
	 0.0f,  0.0f,  1.0f,  // top-right
	 0.0f,  0.0f,  1.0f,  // top-right
	 0.0f,  0.0f,  1.0f,  // top-left
	 0.0f,  0.0f,  1.0f,  // bottom-left
	// left face
	-1.0f,  0.0f,  0.0f,  // top-right
	-1.0f,  0.0f,  0.0f,  // top-left
	-1.0f,  0.0f,  0.0f,  // bottom-left
	-1.0f,  0.0f,  0.0f,  // bottom-left
	-1.0f,  0.0f,  0.0f,  // bottom-right
	-1.0f,  0.0f,  0.0f,  // top-right
	// right face
	 1.0f,  0.0f,  0.0f,  // top-left
	 1.0f,  0.0f,  0.0f,  // bottom-right
	 1.0f,  0.0f,  0.0f,  // top-right
	 1.0f,  0.0f,  0.0f,  // bottom-right
	 1.0f,  0.0f,  0.0f,  // top-left
	 1.0f,  0.0f,  0.0f,  // bottom-left
	// bottom face
	 0.0f, -1.0f,  0.0f,  // top-right
	 0.0f, -1.0f,  0.0f,  // top-left
	 0.0f, -1.0f,  0.0f,  // bottom-left
	 0.0f, -1.0f,  0.0f,  // bottom-left
	 0.0f, -1.0f,  0.0f,  // bottom-right
	 0.0f, -1.0f,  0.0f,  // top-right
	// top face
	 0.0f,  1.0f,  0.0f,  // top-left
	 0.0f,  1.0f,  0.0f,  // bottom-right
	 0.0f,  1.0f,  0.0f,  // top-right
	 0.0f,  1.0f,  0.0f,  // bottom-right
	 0.0f,  1.0f,  0.0f,  // top-left
	 0.0f,  1.0f,  0.0f,  // bottom-left
};

static std::vector<float> _box_uv 
{
	// back face
	0.0f, 0.0f, // bottom-left
	1.0f, 1.0f, // top-right
	1.0f, 0.0f, // bottom-right
	1.0f, 1.0f, // top-right
	0.0f, 0.0f, // bottom-left
	0.0f, 1.0f, // top-left
	// front face
	1.0f, 0.0f, // bottom-left
	0.0f, 0.0f, // bottom-right
	0.0f, 1.0f, // top-right
	0.0f, 1.0f, // top-right
	1.0f, 1.0f, // top-left
	1.0f, 0.0f, // bottom-left
	// left face
	1.0f, 1.0f, // top-right
	1.0f, 0.0f, // top-left
	0.0f, 0.0f, // bottom-left
	0.0f, 0.0f, // bottom-left
	0.0f, 1.0f, // bottom-right
	1.0f, 1.0f, // top-right
	// right face
	0.0f, 1.0f, // top-left
	0.0f, 0.0f, // bottom-right
	1.0f, 0.0f, // top-right
	1.0f, 0.0f, // bottom-right
	1.0f, 1.0f, // top-left
	0.0f, 1.0f, // bottom-left
	// bottom face
	0.0f, 0.0f, // top-right
	1.0f, 0.0f, // top-left
	1.0f, 1.0f, // bottom-left
	1.0f, 1.0f, // bottom-left
	0.0f, 1.0f, // bottom-right
	0.0f, 0.0f, // top-right
	// top face
	0.0f, 1.0f, // top-left
	1.0f, 0.0f, // bottom-right
	1.0f, 1.0f, // top-right
	1.0f, 0.0f, // bottom-right
	0.0f, 1.0f, // top-left
	0.0f, 0.0f  // bottom-left
};

static std::vector<float> _box_tangent
{
  // back face
	-1.0f,  0.0f,  0.0f,  // bottom-left
	-1.0f,  0.0f,  0.0f,  // top-right
	-1.0f,  0.0f,  0.0f,  // bottom-right
	-1.0f,  0.0f,  0.0f,  // top-right
	-1.0f,  0.0f,  0.0f,  // bottom-left
	-1.0f,  0.0f,  0.0f,  // top-left
	// front face
	 1.0f,  0.0f,  0.0f,  // bottom-left
	 1.0f,  0.0f,  0.0f,  // bottom-right
	 1.0f,  0.0f,  0.0f,  // top-right
	 1.0f,  0.0f,  0.0f,  // top-right
	 1.0f,  0.0f,  0.0f,  // top-left
	 1.0f,  0.0f,  0.0f,  // bottom-left
	// left face
	 0.0f,  0.0f,  1.0f,   // top-right
	 0.0f,  0.0f,  1.0f,   // top-left
	 0.0f,  0.0f,  1.0f,   // bottom-left
	 0.0f,  0.0f,  1.0f,   // bottom-left
	 0.0f,  0.0f,  1.0f,   // bottom-right
	 0.0f,  0.0f,  1.0f,   // top-right
	// right face
	 0.0f,  0.0f, -1.0f,  // top-left
	 0.0f,  0.0f, -1.0f,  // bottom-right
	 0.0f,  0.0f, -1.0f,  // top-right
	 0.0f,  0.0f, -1.0f,  // bottom-right
	 0.0f,  0.0f, -1.0f,  // top-left
	 0.0f,  0.0f, -1.0f,  // bottom-left
	// bottom face
	 1.0f,  0.0f,  0.0f,  // top-right
	 1.0f,  0.0f,  0.0f,  // top-left
	 1.0f,  0.0f,  0.0f,  // bottom-left
	 1.0f,  0.0f,  0.0f,  // bottom-left
	 1.0f,  0.0f,  0.0f,  // bottom-right
	 1.0f,  0.0f,  0.0f,  // top-right
	// top face
	 1.0f,  0.0f,  0.0f,  // top-left
	 1.0f,  0.0f,  0.0f,  // bottom-right
	 1.0f,  0.0f,  0.0f,  // top-right
	 1.0f,  0.0f,  0.0f,  // bottom-right
	 1.0f,  0.0f,  0.0f,  // top-left
	 1.0f,  0.0f,  0.0f,  // bottom-left
};

static std::vector<float> _box_bitangent
{
  // back face
	 0.0f,  1.0f,  0.0f,  // bottom-left
	 0.0f,  1.0f,  0.0f,  // top-right
	 0.0f,  1.0f,  0.0f,  // bottom-right
	 0.0f,  1.0f,  0.0f,  // top-right
	 0.0f,  1.0f,  0.0f,  // bottom-left
	 0.0f,  1.0f,  0.0f,  // top-left
	// front face
	 0.0f,  1.0f,  0.0f,  // bottom-left
	 0.0f,  1.0f,  0.0f,  // bottom-right
	 0.0f,  1.0f,  0.0f,  // top-right
	 0.0f,  1.0f,  0.0f,  // top-right
	 0.0f,  1.0f,  0.0f,  // top-left
	 0.0f,  1.0f,  0.0f,  // bottom-left
	// left face
	 0.0f,  1.0f,  0.0f,   // top-right
	 0.0f,  1.0f,  0.0f,   // top-left
	 0.0f,  1.0f,  0.0f,   // bottom-left
	 0.0f,  1.0f,  0.0f,   // bottom-left
	 0.0f,  1.0f,  0.0f,   // bottom-right
	 0.0f,  1.0f,  0.0f,   // top-right
	// right face
	 0.0f,  1.0f,  0.0f,  // top-left
	 0.0f,  1.0f,  0.0f,  // bottom-right
	 0.0f,  1.0f,  0.0f,  // top-right
	 0.0f,  1.0f,  0.0f,  // bottom-right
	 0.0f,  1.0f,  0.0f,  // top-left
	 0.0f,  1.0f,  0.0f,  // bottom-left
	// bottom face
	 0.0f,  0.0f,  1.0f,  // top-right
	 0.0f,  0.0f,  1.0f,  // top-left
	 0.0f,  0.0f,  1.0f,  // bottom-left
	 0.0f,  0.0f,  1.0f,  // bottom-left
	 0.0f,  0.0f,  1.0f,  // bottom-right
	 0.0f,  0.0f,  1.0f,  // top-right
	// top face
	 1.0f,  0.0f,  0.0f,  // top-left
	 1.0f,  0.0f,  0.0f,  // bottom-right
	 1.0f,  0.0f,  0.0f,  // top-right
	 1.0f,  0.0f,  0.0f,  // bottom-right
	 1.0f,  0.0f,  0.0f,  // top-left
	 1.0f,  0.0f,  0.0f,  // bottom-left
};

void BoxGeometry::setup()
{
  // 1. set attribs
  addAttr(Attribute(ATTR_TYPE::POSITION , _box_pos      , 3));
  addAttr(Attribute(ATTR_TYPE::NORMAL   , _box_normal   , 3));
  addAttr(Attribute(ATTR_TYPE::UV       , _box_uv       , 2));
  addAttr(Attribute(ATTR_TYPE::TANGENT  , _box_tangent  , 3));
  addAttr(Attribute(ATTR_TYPE::BITANGENT, _box_bitangent, 3));
  
  // 2. set indices
  auto _indices = std::vector<GLuint>(36);
  for(size_t i = 0; i < _indices.size(); ++i)
    _indices[i] = i;
  setIndices(_indices);

  // 3. set buffer
  setBuffer();
}