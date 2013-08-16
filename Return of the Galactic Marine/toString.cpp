#include "toString.h"

#include <sstream>

namespace ToString
{
	std::string toString(int int_arg)
	{
		std::stringstream stringstream_ret;
		stringstream_ret << int_arg;
		return stringstream_ret.str();
	}
	std::string toString(unsigned int uint_arg)
	{
		std::stringstream stringstream_ret;
		stringstream_ret << uint_arg;
		return stringstream_ret.str();
	}
	std::string toString(double double_arg)
	{
		std::stringstream stringstream_ret;
		stringstream_ret << double_arg;
		return stringstream_ret.str();
	}
	std::string toString(float float_arg)
	{
		std::stringstream stringstream_ret;
		stringstream_ret << float_arg;
		return stringstream_ret.str();
	}
	std::string toString(bool bool_arg)
	{
		return (bool_arg) ? "true" : "false";
	}
}