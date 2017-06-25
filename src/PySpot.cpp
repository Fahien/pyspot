#include <Python.h>
#include "PySpot.h"
#include "PySpotString.h"

using namespace pyspot;


PySpot::PySpot()
{
	Py_Initialize();
	PyRun_SimpleString("print('Python initialized')");
}


PySpot::~PySpot()
{
	Py_Finalize();
}


PySpotModule PySpot::importModule(const char * name)
{
	return PySpotModule{ PySpotString{ name } };
}