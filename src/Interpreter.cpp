#include "pyspot/Interpreter.h"
#include "pyspot/Module.h"
#include "pyspot/String.h"
#include "pyspot/Exception.h"

#ifdef _WIN32
# define PATH_SEP ";"
#else
# define PATH_SEP ":"
#endif

using namespace pyspot;


Interpreter::Interpreter()
{
	initialize("/script");
}


Interpreter::Interpreter(const char* dir)
{
	initialize(dir);
}


Interpreter::Interpreter(const std::string& dir)
:	Interpreter{ dir.c_str() }
{}


Interpreter::Interpreter(const char* import, void (*function)(void))
:	Interpreter{ import, function, "/script" }
{}


Interpreter::Interpreter(const char* import, void (*function)(void), const char* dir)
{
	if (PyImport_AppendInittab(import, function) < 0)
	{
		throw Exception{ "Cannot import" };
	}
	initialize(dir);
}


Interpreter::Interpreter(const char* import, void (*function)(void), const std::string& dir)
:	Interpreter{ import, function, dir.c_str() }
{}


Interpreter::~Interpreter()
{
	Py_Finalize();
}


void Interpreter::initialize(const char * dir)
{
	Py_Initialize();
	addToPath(dir);
}


Module Interpreter::ImportModule(const std::string& name)
{
	return ImportModule(name.c_str());
}


Module Interpreter::ImportModule(const char* name)
{
	return Module{ String{ name } };
}


void Interpreter::addToPath(const char* folder)
{
	std::string path{ Py_GetPath() };
	path += PATH_SEP;
	path += folder;
	PySys_SetPath(&path[0]);
}
