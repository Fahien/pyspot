#include "pyspot/String.h"

#include <Python.h>

using namespace pyspot;


String::String(PyObject* object)
:	Object{ object }
{}


String::String(const char* str)
:	String{ PyUnicode_FromString(str) }
{}


String::~String()
{}
