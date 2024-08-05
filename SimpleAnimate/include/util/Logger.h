#include <iostream>
#include <iomanip>
#include <glm/glm.hpp>

namespace SA
{
	class Logger
	{
	public:
		Logger() {}
		template <typename T>
		const Logger& log( const T val , const std::string& name = "unknown variable" ) const
		{
			std::cout << "Unsupported type log, omit..." << std::endl;
			return *this;
		}
	};
	template <>
	const Logger& Logger::log<int>( const int val , const std::string& name ) const
	{
		std::cout << name << ":" << std::endl
			<< val << std::endl
			<< std::endl;
		return *this;
	}
	template <>
	const Logger& Logger::log<float>( const float val , const std::string& name ) const
	{
		std::cout << name << ":" << std::endl
			<< val << std::endl
			<< std::endl;
		return *this;
	}
	template <>
	const Logger& Logger::log<glm::vec3>( const glm::vec3 val , const std::string& name ) const
	{
		std::cout << name << ":" << std::endl
			<< std::setprecision( 3 ) << std::setiosflags( std::ios::right )
			<< "(" << std::setw( 6 ) << val[0] << "," << std::setw( 6 ) << val[1] << "," << std::setw( 6 ) << val[2] << " )" << std::endl
			<< std::endl;
		return *this;
	}
	template <>
	const Logger& Logger::log<glm::mat3>( const glm::mat3 val , const std::string& name ) const
	{
		std::cout << name << ":" << std::endl
			<< std::setprecision( 3 ) << std::setiosflags( std::ios::right )
			<< "[(" << std::setw( 6 ) << val[0][0] << "," << std::setw( 6 ) << val[0][1] << "," << std::setw( 6 ) << val[0][2] << " )," << std::endl
			<< " (" << std::setw( 6 ) << val[1][0] << "," << std::setw( 6 ) << val[1][1] << "," << std::setw( 6 ) << val[1][2] << " )," << std::endl
			<< " (" << std::setw( 6 ) << val[2][0] << "," << std::setw( 6 ) << val[2][1] << "," << std::setw( 6 ) << val[2][2] << " )]" << std::endl
			<< std::endl;
		return *this;
	}
	template <>
	const Logger& Logger::log<glm::mat4>( const glm::mat4 val , const std::string& name ) const
	{
		std::cout << name << ":" << std::endl
			<< std::setprecision( 3 ) << std::setiosflags( std::ios::right )
			<< "[(" << std::setw( 6 ) << val[0][0] << "," << std::setw( 6 ) << val[0][1] << "," << std::setw( 6 ) << val[0][2] << "," << std::setw( 6 ) << val[0][3] << " )," << std::endl
			<< " (" << std::setw( 6 ) << val[1][0] << "," << std::setw( 6 ) << val[1][1] << "," << std::setw( 6 ) << val[1][2] << "," << std::setw( 6 ) << val[1][3] << " )," << std::endl
			<< " (" << std::setw( 6 ) << val[2][0] << "," << std::setw( 6 ) << val[2][1] << "," << std::setw( 6 ) << val[2][2] << "," << std::setw( 6 ) << val[2][3] << " )," << std::endl
			<< " (" << std::setw( 6 ) << val[3][0] << "," << std::setw( 6 ) << val[3][1] << "," << std::setw( 6 ) << val[3][2] << "," << std::setw( 6 ) << val[3][3] << " )]" << std::endl
			<< std::endl;

		return *this;
	}

	Logger logger{};
} // namespace SA
