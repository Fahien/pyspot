#ifndef PST_EXCEPTION_H_
#define PST_EXCEPTION_H_

#include <stdexcept>


namespace pyspot
{

class Exception : public std::runtime_error
{
  public:
	Exception(const char* msg)
	:	std::runtime_error{ msg }
	{}

	Exception(const std::string& msg)
	: std::runtime_error{ msg }
	{}
};

}

#endif // PST_EXCEPTION_H_
