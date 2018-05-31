#include "pyspot/String.h"

#include <Python.h>

using namespace pyspot;


String::String(PyObject* object)
:	Object{ object }
{}


String::String(const char* str)
{
	mObject = PyUnicode_FromString(str);
}


String::~String()
{}
