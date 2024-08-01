#pragma once

#include <array>
#include <vector>

#include <geometry/GeometryVAO.h>
#include <geometry/Attribute.h>

namespace SA
{

	namespace GEOMETRY
	{
		enum SA_API SHAPE : size_t
		{
			PLANE,
			BOX,
			NR_SHAPE
		};

	} // namespace GEOMETRY

	class SA_API Geometry
	{
	public:
		void setBuffer();
		void addAttr(const Attribute &attr);
		void setIndices(const std::vector<GLuint> &indices);
		virtual void draw() = 0;

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
