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


pst::PySpot::PySpot(const std::wstring& dir)
:	PySpot{ dir.c_str() }
{}


pst::PySpot::PySpot(const char* import, PyObject* (*function)(void))
:	PySpot{ import, function, L"/script" }
{}


pst::PySpot::PySpot(const char* import, PyObject* (*function)(void), const wchar_t* dir)
{
	PyImport_AppendInittab(import, function);
	initialize(dir);
}


pst::PySpot::PySpot(const char* import, PyObject* (*function)(void), const std::wstring& dir)
:	PySpot{ import, function, dir.c_str() }
{}


pst::PySpot::~PySpot()
{
	Py_Finalize();
}


void pst::PySpot::initialize(const wchar_t* dir)
{
	Py_Initialize();
	addToPath(dir);
}


pst::PySpotModule pst::PySpot::ImportModule(const std::string& name)
{
	return ImportModule(name.c_str());
}


pst::PySpotModule pst::PySpot::ImportModule(const char* name)
{
	return pst::PySpotModule{ pst::PySpotString{ name } };
}


void pst::PySpot::addToPath(const wchar_t* folder)
{
	pst::PySpotModule os { ImportModule("os") };
	pst::PySpotObject cwd{ os.CallFunction("getcwd") };
	std::wstring path{ Py_GetPath() + (L";" + cwd.ToString()) + folder };
	PySys_SetPath(path.c_str());
}
