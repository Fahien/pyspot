#ifndef PST_EXCEPTION_H_
#define PST_EXCEPTION_H_

#include <stdexcept>

#include "pyspot/Common.h"

namespace pyspot
{


class Exception : public std::exception
{
  public:
	Exception( cstring msg ) : message{ msg }
	{
		str_message.reserve( message.length() );
		std::wcstombs( str_message.data(), message.c_str(), message.length() );
	}

	Exception( const tstring& msg ) : Exception{ msg.c_str() } {}

	const tstring& get_message() const { return message; }

	const char* what() const noexcept override { return str_message.c_str(); }

  private:
	const tstring message;
	std::string   str_message;
};


}  // namespace pyspot

#endif  // PST_EXCEPTION_H_
