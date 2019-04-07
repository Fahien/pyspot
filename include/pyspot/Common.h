#ifndef PST_COMMON_H_
#define PST_COMMON_H_

#include <Python.h>
#include <string>

namespace pyspot
{


#define _T( x ) L##x
using init_f  = PyObject* (*)( void );
using cstring = const wchar_t*;
using tstring = std::wstring;


inline tstring to_tstring( const std::string& s )
{
	std::wstring ret;
	ret.assign( std::begin( s ), std::end( s ) );
	return ret;
}


}  // namespace pyspot

#endif  // PST_COMMON_H_
