#include <Python.h>
#include "PySpot.h"
#include "PySpotModule.h"

using namespace pyspot;


PySpot::PySpot()
{
	Py_Initialize();
	addToPath(L"/script");
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


void PySpot::addToPath(const wchar_t * folder)
{
	PySpotModule os { importModule("os") };
	PySpotObject cwd{ os.callFunction("getcwd") };
	printf("Result = %ls\n", cwd.toString().c_str());
	std::wstring path{ Py_GetPath() + (L";" + cwd.toString()) + folder };
	printf("Python search path is %ls\n", path.c_str());
	PySys_SetPath(path.c_str());
}