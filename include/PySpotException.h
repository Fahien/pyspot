#ifndef PST_PYSPOTEXCEPTION_H
#define PST_PYSPOTEXCEPTION_H

#include <stdexcept>

namespace pyspot
{

class PySpotException : public std::runtime_error
{
public:
	PySpotException(const char* msg)
	:	std::runtime_error{ msg }
	{}
};

}

#endif // PST_PYSPOTEXCEPTION_H
