#include "pyspot/String.h"

#include <Python.h>


namespace pyspot
{


String::String(PyObject* object)
:	Object{ object }
,	mStr { Object::ToString()  }
,	mWStr{ Object::ToWString() }
{}

String::String(const Object& object)
:	Object{ object }
,	mStr { Object::ToString()  }
,	mWStr{ Object::ToWString() }
{}

String::String(const std::wstring& str)
:	String{ PyUnicode_FromWideChar(str.c_str(), str.length()) }
{}

String::String(const std::string& str)
:	String{ PyUnicode_FromString(str.c_str()) }
{}


String::~String()
{}


} // namespace pyspot
