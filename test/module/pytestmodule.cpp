#include "pytestmodule.h"


#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

static PyObject * pytestError;

PyObject * invoke(PyObject * object)
{
	printf("Inside invoke function\n");
	PyErr_SetString(pytestError, "C raised exception");
	Py_RETURN_NONE;
}

struct module_state {
	PyObject *error;
};

static PyMethodDef myextension_methods[] {
	{"invoke", (PyCFunction)invoke, METH_NOARGS, nullptr},
	{nullptr, nullptr}
};

static struct PyModuleDef moduledef {
	PyModuleDef_HEAD_INIT,
	"pytest",
	nullptr,
	sizeof(struct module_state),
	myextension_methods,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};

PyMODINIT_FUNC PyInit_pytest()
{
	// Create the module
	PyObject * object { PyModule_Create(&moduledef) };
	if (object == nullptr)
	{
		return nullptr;
	}

	// Module exception
	pytestError = PyErr_NewException("pytest.error", nullptr, nullptr);
	Py_INCREF(pytestError);
	PyModule_AddObject(object, "error", pytestError);

	return object;
}
