#include <Python.h>
#include <string>

#include "pyspot/String.h"
#include "pyspot/Module.h"
#include "pyspot/Exception.h"
#include "pyspot/Error.h"


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

	if (traceback)
	{
		/* See if we can get a full traceback */
		auto tracebackModule = Module{ "traceback" };

		PyObject *pyth_func = PyObject_GetAttrString(tracebackModule.GetObject(), "format_exception");
		if (pyth_func && PyCallable_Check(pyth_func))
		{
			PyObject *pyth_val;

			pyth_val = PyObject_CallFunctionObjArgs(pyth_func, type, value, traceback, NULL);
			ret += String{ PyObject_Str(pyth_val) }.ToTString();
			Py_XDECREF(pyth_val);
		}

		ret += String{ PyObject_Repr(traceback) }.ToTString();
	}

	PyErr_Clear();

	return ret;
}
