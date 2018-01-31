#include "PySpotString.h"

#include <Python.h>

using namespace pyspot;


PySpotString::PySpotString(PyObject* object)
:	PySpotObject{ object }
{}


PySpotString::PySpotString(const char* str)
{
	mObject = PyUnicode_FromString(str);
}


PySpotString::~PySpotString()
{}
