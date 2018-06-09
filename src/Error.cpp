#include <Python.h>

#include "pyspot/Error.h"


using namespace std;
using namespace pyspot;


string Error::Get()
{
	PyObject *type, *value, *traceback;
	// Fetch the current exception
	PyErr_Fetch(&type, &value, &traceback);

	PyObject* mod{ PyImport_ImportModule("traceback") };
	if (!mod)
	{
		return "Cannot import traceback";
	}

	// Invoke traceback.format_exception
	PyObject* list{ PyObject_CallMethod(mod, "format_exception", "OOO", type, value, traceback) };

	PyObject* newline{ PyUnicode_FromString("\n")    };
	PyObject* message{ PyUnicode_Join(newline, list) };
	Py_DECREF(list);
	Py_DECREF(newline);

	string ret{ PyUnicode_AsUTF8(message) };
	Py_DECREF(message);
	PyErr_Clear();

	return ret;
}
