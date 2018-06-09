#include "pyspot/String.h"

#include <Python.h>

using namespace pyspot;


String::String(PyObject* object)
:	Object{ object }
,	mCStr{ Object::ToCString() }
{}


String::String(const char* str)
:	String{ PyUnicode_FromString(str) }
{}


String::~String()
{}
