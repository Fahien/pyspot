#ifndef PST_EXCEPTION_H_
#define PST_EXCEPTION_H_

#include <stdexcept>

#include "pyspot/Common.h"


namespace pyspot
{
class Exception : public std::exception
{
  public:
	Exception( cstring msg ) : message{ msg } {}

	Exception( const tstring& msg ) : message{ msg } {}

	const tstring& get_message() const { return message; }

  private:
	const tstring message;
};

}  // namespace pyspot

#endif  // PST_EXCEPTION_H_
