#ifndef PST_EXCEPTION_H_
#define PST_EXCEPTION_H_

#include <stdexcept>

#include "pyspot/common.h"


namespace pyspot
{

class Exception : public std::exception
{
  public:
	Exception(cstring msg)
	:	mMsg{ msg }
	{}

	Exception(const tstring& msg)
	:	mMsg{ std::move(msg) }
	{}

	const tstring& What() const { return mMsg; }

  private:
	const tstring mMsg;
};

}

#endif // PST_EXCEPTION_H_
