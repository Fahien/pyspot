#ifndef PST_COMMON_H_
#define PST_COMMON_H_

#include <string>
#include <Python.h>


namespace pyspot
{

#if PYTHON_VERSION >= 3
#define _T(x) L ##x
using init_f = PyObject* (*)(void);
using cstring = const wchar_t*;
using tstring  = std::wstring;
#else
#define _T(x) x
using init_f = void (*)(void);
using cstring = const char*;
using tstring  = std::string;
#endif


#if PYTHON_VERSION >= 3
inline tstring to_tstring(const std::string& s)
{
	std::wstring ret;
	ret.assign(std::begin(s), std::end(s));
	return ret;
}
#else
inline tstring& to_tstring(std::string& s)
{
	return s;
}
#endif


} // namespace pyspot


#endif // PST_COMMON_H_
