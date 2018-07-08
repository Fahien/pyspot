#ifndef PST_COMMON_H_
#define PST_COMMON_H_

#include <string>


namespace pyspot
{

#if PYTHON_VERSION >= 3
#define _T(x) L ##x
using init_f = PyObject* (*)(void);
using cstring = const wchar_t*;
using string  = std::wstring;
#else
#define _T(x) x
using init_f = void (*)(void);
using cstring = const char*;
using string  = std::string;
#endif

}


#endif // PST_COMMON_H_
