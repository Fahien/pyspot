#include "PySpot.h"
#include "PySpotModule.h"
#include "PySpotString.h"

namespace pst = pyspot;


pst::PySpot::PySpot()
{
	Py_Initialize();
	addToPath(L"/script");
	printf("Python initialized\n");
}


pst::PySpot::PySpot(const char* import, PyObject* (*function)(void))
{
	PyImport_AppendInittab(import, function);
	Py_Initialize();
	addToPath(L"/script");
	printf("Python initialized\n");
}


pst::PySpot::~PySpot()
{
	printf("Destroying Pyspot\n");
	Py_Finalize();
}


pst::PySpotModule pst::PySpot::ImportModule(const char* name)
{
	return pst::PySpotModule{ pst::PySpotString{ name } };
}


void pst::PySpot::addToPath(const wchar_t* folder)
{
	pst::PySpotModule os { ImportModule("os") };
	pst::PySpotObject cwd{ os.CallFunction("getcwd") };
	printf("Result = %ls\n", cwd.ToString().c_str());
	std::wstring path{ Py_GetPath() + (L";" + cwd.ToString()) + folder };
	printf("Python search path is %ls\n", path.c_str());
	PySys_SetPath(path.c_str());
}
