#pragma once

#include <array>
#include <vector>

#include <GeometryVAO.h>
#include <Attribute.h>

namespace SA
{

	namespace GEOMETRY
	{
		enum SHAPE : size_t
		{
			PLANE,
			BOX,
			NR_SHAPE
		};

	}

	class Geometry
	{
	public:
		void setBuffer();
		void addAttr(const Attribute &attr);
		void setIndices(const std::vector<GLuint> &indices);

	protected:
		Geometry();

		GeometryVAO VAO;
		GEOMETRY::SHAPE _shape;
		std::array<Attribute, ATTR_TYPE::NR_ATTR_TYPE> attributes;
		bool _buf_needs_update = true;

		virtual void setup() = 0;

	private:
	};

}
