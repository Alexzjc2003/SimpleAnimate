#pragma once

// #include <iostream>
#include <sstream>
#include <iomanip>
#include <glm/glm.hpp>
#include <def.h>
#include <core/Proxy.h>

namespace SA
{
	class SA_API Logger
	{
	public:
		Logger() {}
		template <typename T>
		Logger& log(const T val, const std::string& name = "unknown variable")
		{
			//std::cout << "Unsupported type log, omit..." << std::endl;
			_ss
				<< name << ":" << std::endl
				<< "Unsupported type log, omit..." << std::endl
				<< std::endl;
			return *this;
		}

		template <>
		Logger& log<int>(const int, const std::string&);

		template <>
		Logger& log<float>(const float, const std::string&);

		template <>
		Logger& log<double>(const double, const std::string&);

		template <>
		Logger& log<glm::vec3>(const glm::vec3, const std::string&);

		template <>
		Logger& log<glm::mat3>(const glm::mat3, const std::string&);

		template <>
		Logger& log<glm::mat4>(const glm::mat4, const std::string&);

		template <typename Tval>
		Logger& log(const Proxy<Tval>& proxy, const std::string& name)
		{
			log(proxy.clone(), name);
		}

		void flush(const double delta);
		double flush_gap = 1;
		double flush_remain = 1;

	private:
		std::stringstream _ss;
	};

	extern SA_API Logger logger;
} // namespace SA
