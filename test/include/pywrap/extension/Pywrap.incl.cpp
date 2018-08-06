#include <pyspot/String.h>

using namespace pyspot;


static PyObject* GetStringFromC(PyObject* self, PyObject* args)
{
	return String{ "PyWrap" }.GetIncref();
}
