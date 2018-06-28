#include <Python.h>
#include <string>

#include "pyspot/String.h"
#include "pyspot/Module.h"
#include "pyspot/Exception.h"
#include "pyspot/Error.h"


using namespace std;
using namespace pyspot;


void Error::Check()
{
	if (PyErr_Occurred())
	{
		throw Exception{ Get() };
	}
}


string Error::Get()
{
	PyObject *type, *value, *traceback;
	// Fetch the current exception
	PyErr_Fetch(&type, &value, &traceback);

	string ret{ "" };
	ret += String{ PyObject_Repr(type) }.ToString();
	ret += String{ PyObject_Repr(value) }.ToString();

	if (traceback) {
		/* See if we can get a full traceback */
		PyObject *module_name = PyString_FromString("traceback");
		PyObject *pyth_module = PyImport_Import(module_name);
		Py_DECREF(module_name);

		if (pyth_module == NULL) {
			return ret;
		}

		PyObject *pyth_func = PyObject_GetAttrString(pyth_module, "format_exception");
		if (pyth_func && PyCallable_Check(pyth_func)) {
			PyObject *pyth_val;

			pyth_val = PyObject_CallFunctionObjArgs(pyth_func, type, value, traceback, NULL);

			PyObject *pystr = PyObject_Str(pyth_val);
			ret += PyString_AsString(pystr);
			Py_XDECREF(pyth_val);
		}

		ret += String{PyObject_Repr(traceback)}.ToString();
	}

	PyErr_Clear();

	return ret;
}
