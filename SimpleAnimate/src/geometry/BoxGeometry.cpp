#include "pch.h"
#include "geometry/BoxGeometry.h"

using namespace SA;

static std::vector<float> _box_pos
{
	// back face		// negativeZ
	-0.5f, -0.5f, -0.5f,  // bottom-left
	 0.5f,  0.5f, -0.5f,  // top-right
	 0.5f, -0.5f, -0.5f,  // bottom-right
	 0.5f,  0.5f, -0.5f,  // top-right
	-0.5f, -0.5f, -0.5f,  // bottom-left
	-0.5f,  0.5f, -0.5f,  // top-left
	// front face		// positiveZ
	-0.5f, -0.5f,  0.5f,  // bottom-left
	 0.5f, -0.5f,  0.5f,  // bottom-right
	 0.5f,  0.5f,  0.5f,  // top-right
	 0.5f,  0.5f,  0.5f,  // top-right
	-0.5f,  0.5f,  0.5f,  // top-left
	-0.5f, -0.5f,  0.5f,  // bottom-left
	// left face		// negativeX
	-0.5f,  0.5f,  0.5f,  // top-front
	-0.5f,  0.5f, -0.5f,  // top-back
	-0.5f, -0.5f, -0.5f,  // bottom-back
	-0.5f, -0.5f, -0.5f,  // bottom-back
	-0.5f, -0.5f,  0.5f,  // bottom-front
	-0.5f,  0.5f,  0.5f,  // top-front
	// right face		// positiveX
	 0.5f,  0.5f,  0.5f,  // top-front
	 0.5f, -0.5f, -0.5f,  // bottom-back
	 0.5f,  0.5f, -0.5f,  // top-back
	 0.5f, -0.5f, -0.5f,  // bottom-back
	 0.5f,  0.5f,  0.5f,  // top-front
	 0.5f, -0.5f,  0.5f,  // bottom-front
	// bottom face	// negativeY
	-0.5f, -0.5f, -0.5f,  // back-left
	 0.5f, -0.5f, -0.5f,  // back-right
	 0.5f, -0.5f,  0.5f,  // front-right
	 0.5f, -0.5f,  0.5f,  // front-right
	-0.5f, -0.5f,  0.5f,  // front-left
	-0.5f, -0.5f, -0.5f,  // back-left
	// top face			// positiveY
	-0.5f,  0.5f, -0.5f,  // back-left
	 0.5f,  0.5f,  0.5f,  // front-right
	 0.5f,  0.5f, -0.5f,  // back-right
	 0.5f,  0.5f,  0.5f,  // front-right
	-0.5f,  0.5f, -0.5f,  // back-left
	-0.5f,  0.5f,  0.5f,  // front-left
};

static std::vector<float> _box_normal
{
	// back face
	 0.0f,  0.0f, -1.0f,  
	 0.0f,  0.0f, -1.0f,  
	 0.0f,  0.0f, -1.0f,  
	 0.0f,  0.0f, -1.0f,  
	 0.0f,  0.0f, -1.0f,  
	 0.0f,  0.0f, -1.0f,  
	// front face
	 0.0f,  0.0f,  1.0f,  
	 0.0f,  0.0f,  1.0f,  
	 0.0f,  0.0f,  1.0f,  
	 0.0f,  0.0f,  1.0f,  
	 0.0f,  0.0f,  1.0f,  
	 0.0f,  0.0f,  1.0f,  
	// left face
	-1.0f,  0.0f,  0.0f,  
	-1.0f,  0.0f,  0.0f,  
	-1.0f,  0.0f,  0.0f,  
	-1.0f,  0.0f,  0.0f,  
	-1.0f,  0.0f,  0.0f,  
	-1.0f,  0.0f,  0.0f,  
	// right face
	 1.0f,  0.0f,  0.0f,  
	 1.0f,  0.0f,  0.0f,  
	 1.0f,  0.0f,  0.0f,  
	 1.0f,  0.0f,  0.0f,  
	 1.0f,  0.0f,  0.0f,  
	 1.0f,  0.0f,  0.0f,  
	// bottom face
	 0.0f, -1.0f,  0.0f,  
	 0.0f, -1.0f,  0.0f,  
	 0.0f, -1.0f,  0.0f,  
	 0.0f, -1.0f,  0.0f,  
	 0.0f, -1.0f,  0.0f,  
	 0.0f, -1.0f,  0.0f,  
	// top face
	 0.0f,  1.0f,  0.0f,  
	 0.0f,  1.0f,  0.0f,  
	 0.0f,  1.0f,  0.0f,  
	 0.0f,  1.0f,  0.0f,  
	 0.0f,  1.0f,  0.0f,  
	 0.0f,  1.0f,  0.0f,  
};

static std::vector<float> _box_uv 
{
	// back face
	1.0f, 0.0f, // bottom-left
	0.0f, 1.0f, // top-right
	0.0f, 0.0f, // bottom-right
	0.0f, 1.0f, // top-right
	1.0f, 0.0f, // bottom-left
	1.0f, 1.0f, // top-left
	// front face
	0.0f, 0.0f, // bottom-left
	1.0f, 0.0f, // bottom-right
	1.0f, 1.0f, // top-right
	1.0f, 1.0f, // top-right
	0.0f, 1.0f, // top-left
	0.0f, 0.0f, // bottom-left
	// left face
	1.0f, 1.0f, // top-front
	0.0f, 1.0f, // top-back
	0.0f, 0.0f, // bottom-back
	0.0f, 0.0f, // bottom-back
	1.0f, 0.0f, // bottom-front
	1.0f, 1.0f, // top-front
	// right face
	0.0f, 1.0f, // top-front
	1.0f, 0.0f, // bottom-back
	1.0f, 1.0f, // top-back
	1.0f, 0.0f, // bottom-back
	0.0f, 1.0f, // top-front
	0.0f, 0.0f, // bottom-front
	// bottom face
	1.0f, 0.0f, // back-left
	0.0f, 0.0f, // back-right
	0.0f, 1.0f, // front-right
	0.0f, 1.0f, // front-right
	1.0f, 1.0f, // front-left
	1.0f, 0.0f, // back-left
	// top face
	1.0f, 0.0f, // back-left
	0.0f, 1.0f, // front-right
	0.0f, 0.0f, // back-right
	0.0f, 1.0f, // front-right
	1.0f, 0.0f, // back-left
	1.0f, 1.0f  // front-left
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

// FIXME: fix the directions and comments
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

BoxGeometry::BoxGeometry() : Geometry()
{
	setup();
}

void BoxGeometry::setup()
{
  // 1. set attribs
  addAttr(Attribute(ATTR_TYPE::POSITION , _box_pos      , 3));
  addAttr(Attribute(ATTR_TYPE::NORMAL   , _box_normal   , 3));
  addAttr(Attribute(ATTR_TYPE::UV       , _box_uv       , 2));
  addAttr(Attribute(ATTR_TYPE::TANGENT  , _box_tangent  , 3));
  addAttr(Attribute(ATTR_TYPE::BITANGENT, _box_bitangent, 3));
  
  // 2. set buffer
  setBuffer();

  // 3. set indices
  auto _indices = std::vector<GLuint>(36);
  for(size_t i = 0; i < _indices.size(); ++i)
    _indices[i] = i;
  setIndices(_indices);
}


void BoxGeometry::draw()
{
	VAO.activate();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	VAO.deactivate();
}