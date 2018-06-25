#include <Python.h>
#include <string>

#include "pyspot/String.h"
#include "pyspot/Error.h"


using namespace std;
using namespace pyspot;


string Error::Get()
{
	PyObject *type, *value, *traceback;
	// Fetch the current exception
	PyErr_Fetch(&type, &value, &traceback);

	string ret{ "" };
    ret += String{ PyObject_Repr(type) }.ToString();
    ret += String{ PyObject_Repr(value) }.ToString();
    ret += String{ PyObject_Repr(traceback) }.ToString();

	PyErr_Clear();

	return ret;
}
