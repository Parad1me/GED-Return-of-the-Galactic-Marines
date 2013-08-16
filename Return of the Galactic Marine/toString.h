#ifndef TO_STRING
#define TO_STRING

#include <string>

namespace ToString
{
	std::string toString(int int_arg);
	std::string toString(unsigned int uint_arg);
	std::string toString(double double_arg);
	std::string toString(float float_arg);
	std::string toString(bool bool_arg);
}

#endif