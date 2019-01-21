#ifndef PST_EXCEPTION_H_
#define PST_EXCEPTION_H_

#include <stdexcept>

#include "pyspot/Common.h"


namespace pyspot
{

class Exception : public std::runtime_error
{
  public:
	Exception(cstring msg)
	:	std::runtime_error{ msg }
	,	mMsg{ msg }
	{}

	Exception(const tstring& msg)
	: Exception{ msg.c_str() }
	{}

	const tstring& What() const { return mMsg; }

  private:
	const tstring mMsg;
};

}

#endif // PST_EXCEPTION_H_
