#include "pyspot/String.h"

#include <Python.h>

using namespace pyspot;


String::String(PyObject* object)
:	Object{ object }
,	mStr{ Object::ToString() }
{}


String::String(const std::string& str)
: String{ str.c_str() }
{}


String::String(const char* str)
:	Object{ PyUnicode_FromString(str) }
,	mStr{ str }
{}


String::~String()
{}
