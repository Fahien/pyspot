#include "pyspot/Interpreter.h"

#include "pyspot/Module.h"
#include "pyspot/String.h"
#include "pyspot/Exception.h"

#ifdef _WIN32
# define PATH_SEP _T(";")
#else
# define PATH_SEP _T(":")
#endif


namespace pyspot
{


Interpreter::Interpreter(const tstring& dir)
{
	initialize(dir);
}


Interpreter::Interpreter(const char* import, init_f function, const tstring& dir)
{
	if (PyImport_AppendInittab(import, function) < 0)
	{
		throw Exception{ _T("Cannot import") };
	}
	initialize(dir);
}


Interpreter::~Interpreter()
{
	Py_Finalize();
}


void Interpreter::initialize(const tstring& dir)
{
	Py_Initialize();
	addToPath(dir);
}


void Interpreter::addToPath(const tstring& folder)
{
	tstring path{ Py_GetPath() };
	path += PATH_SEP;
	path += folder;
	PySys_SetPath(&path[0]);
}


} // namespace pyspot
