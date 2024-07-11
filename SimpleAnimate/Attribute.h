#pragma once

#include <array>
#include <vector>
#include <string>

namespace SA
{
	// Be aware when changing following enums
	// should be in the same order as in shaders
	enum ATTR_TYPE : size_t
	{
		POSITION  = 0,
		NORMAL    = 1,
		UV        = 2,
		TANGENT   = 3,
		BITANGENT = 4,
		NR_ATTR_TYPE
	};
	class Attribute
	{
	public:
		Attribute();
		Attribute(const ATTR_TYPE _t, const std::vector<float> &_arr, size_t _sz, bool _isNorm = false);

		std::string name;
		size_t sz;
		size_t cnt;
		bool isNorm;
		ATTR_TYPE type;

		const float *getData() const;
		const std::vector<float> &getArray() const;

	protected:
		std::vector<float> arr;
	};

}
