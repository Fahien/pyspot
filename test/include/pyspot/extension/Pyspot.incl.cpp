#include <iostream>
#include <Python.h>

using namespace std;


static PyObject* invoke(PyObject* self, PyObject* args)
{
	cout << "Within invoke!" << endl;
	Py_INCREF(Py_None);
	return Py_None;
}
