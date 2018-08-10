#include <Python.h>
#include <string>

#include "pyspot/String.h"
#include "pyspot/Module.h"
#include "pyspot/Exception.h"
#include "pyspot/Error.h"
#include "pyspot/Tuple.h"


using namespace pyspot;


void Error::Check()
{
	if (PyErr_Occurred())
	{
		throw Exception{ Get() };
	}
}


tstring Error::Get()
{
	PyObject *type, *value, *traceback;
	// Fetch the current exception
	PyErr_Fetch(&type, &value, &traceback);

	tstring ret;
	ret += String{ PyObject_Repr(type) }.ToTString();
	ret += String{ PyObject_Repr(value) }.ToTString();

	PyErr_Clear();

	return ret;
}
