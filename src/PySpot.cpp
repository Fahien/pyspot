#include "PySpot.h"

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
