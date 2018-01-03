#include "PySpot.h"
#include "PySpotModule.h"
#include "PySpotString.h"

namespace pst = pyspot;


pst::PySpot::PySpot()
{
	initialize(L"/script");
}


pst::PySpot::PySpot(const wchar_t* dir)
{
	initialize(dir);
}


pst::PySpot::PySpot(const char* import, PyObject* (*function)(void))
:	PySpot{ import, function, L"/script" }
{}


pst::PySpot::PySpot(const char* import, PyObject* (*function)(void), const wchar_t* dir)
{
	PyImport_AppendInittab(import, function);
	initialize(dir);
}


pst::PySpot::~PySpot()
{
	printf("Destroying Pyspot\n");
	Py_Finalize();
}


void pst::PySpot::initialize(const wchar_t* dir)
{
	Py_Initialize();
	addToPath(dir);
	printf("Python initialized\n");
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
