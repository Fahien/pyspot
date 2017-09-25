#include <PySpot.h>
#include <PySpotModule.h>

using namespace pyspot;


PySpot::PySpot()
{
	Py_Initialize();
	addToPath(L"/script");
	printf("Python initialized\n");
}


PySpot::PySpot(const char* import, PyObject* (*function)(void))
{
	PyImport_AppendInittab(import, function);
	Py_Initialize();
	addToPath(L"/script");
	printf("Python initialized\n");
}


PySpot::~PySpot()
{
	printf("Destroying Pyspot\n");
	Py_Finalize();
}


PySpotModule PySpot::ImportModule(const char* name)
{
	return PySpotModule{ PySpotString{ name } };
}


void PySpot::addToPath(const wchar_t* folder)
{
	PySpotModule os { ImportModule("os") };
	PySpotObject cwd{ os.CallFunction("getcwd") };
	printf("Result = %ls\n", cwd.ToString().c_str());
	std::wstring path{ Py_GetPath() + (L";" + cwd.ToString()) + folder };
	printf("Python search path is %ls\n", path.c_str());
	PySys_SetPath(path.c_str());
}
