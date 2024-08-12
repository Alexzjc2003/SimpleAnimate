#include "pch.h"
#include "util/Logger.h"

using namespace SA;

template <>
Logger &Logger::log<int>(const int val, const std::string &name)
{
	// std::cout
	_ss
			<< name << ":" << std::endl
			<< val << std::endl
			<< std::endl;
	return *this;
}
template <>
Logger &Logger::log<float>(const float val, const std::string &name)
{
	// std::cout
	_ss
			<< name << ":" << std::endl
			<< val << std::endl
			<< std::endl;
	return *this;
}
template <>
Logger& Logger::log<double>(const double val, const std::string& name)
{
	// std::cout
	_ss
		<< name << ":" << std::endl
		<< val << std::endl
		<< std::endl;
	return *this;
}
template <>
Logger &Logger::log<glm::vec3>(const glm::vec3 val, const std::string &name)
{
	// std::cout
	_ss
			<< name << ":" << std::endl
			<< std::fixed << std::setprecision(3) << std::setiosflags(std::ios::right)
			<< "(" << std::setw(6) << val[0] << "," << std::setw(6) << val[1] << "," << std::setw(6) << val[2] << " )" << std::endl
			<< std::endl;
	return *this;
}
template <>
Logger &Logger::log<glm::mat3>(const glm::mat3 val, const std::string &name)
{
	// std::cout
	_ss
			<< name << ":" << std::endl
			<< std::fixed << std::setprecision(3) << std::setiosflags(std::ios::right)
			<< "[(" << std::setw(6) << val[0][0] << "," << std::setw(6) << val[0][1] << "," << std::setw(6) << val[0][2] << " )," << std::endl
			<< " (" << std::setw(6) << val[1][0] << "," << std::setw(6) << val[1][1] << "," << std::setw(6) << val[1][2] << " )," << std::endl
			<< " (" << std::setw(6) << val[2][0] << "," << std::setw(6) << val[2][1] << "," << std::setw(6) << val[2][2] << " )]" << std::endl
			<< std::endl;
	return *this;
}
template <>
Logger &Logger::log<glm::mat4>(const glm::mat4 val, const std::string &name)
{
	// std::cout
	_ss
			<< name << ":" << std::endl
			<< std::fixed << std::setprecision(3) << std::setiosflags(std::ios::right)
			<< "[(" << std::setw(6) << val[0][0] << "," << std::setw(6) << val[0][1] << "," << std::setw(6) << val[0][2] << "," << std::setw(6) << val[0][3] << " )," << std::endl
			<< " (" << std::setw(6) << val[1][0] << "," << std::setw(6) << val[1][1] << "," << std::setw(6) << val[1][2] << "," << std::setw(6) << val[1][3] << " )," << std::endl
			<< " (" << std::setw(6) << val[2][0] << "," << std::setw(6) << val[2][1] << "," << std::setw(6) << val[2][2] << "," << std::setw(6) << val[2][3] << " )," << std::endl
			<< " (" << std::setw(6) << val[3][0] << "," << std::setw(6) << val[3][1] << "," << std::setw(6) << val[3][2] << "," << std::setw(6) << val[3][3] << " )]" << std::endl
			<< std::endl;

	return *this;
}

SA_API Logger SA::logger{};

void Logger::flush(const double delta)
{
	flush_remain -= delta;

	if (flush_remain > 0)
	{
		_ss.str("");
		_ss.clear();
		return;
	}

	flush_remain = flush_gap;
	system("CLS");
	std::cout << _ss.str() << std::endl;
}