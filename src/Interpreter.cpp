#include "pyspot/Interpreter.h"
#include "pyspot/Module.h"
#include "pyspot/String.h"
#include "pyspot/Exception.h"

using namespace pyspot;


Interpreter::Interpreter()
{
	initialize(L"/script");
}


Interpreter::Interpreter(const wchar_t* dir)
{
	initialize(dir);
}


Interpreter::Interpreter(const std::wstring& dir)
:	Interpreter{ dir.c_str() }
{}


Interpreter::Interpreter(const char* import, PyObject* (*function)(void))
:	Interpreter{ import, function, L"/script" }
{}


Interpreter::Interpreter(const char* import, PyObject* (*function)(void), const wchar_t* dir)
{
	if (PyImport_AppendInittab(import, function) < 0)
	{
		throw Exception{ "Cannot import" };
	}
	initialize(dir);
}


Interpreter::Interpreter(const char* import, PyObject* (*function)(void), const std::wstring& dir)
:	Interpreter{ import, function, dir.c_str() }
{}


Interpreter::~Interpreter()
{
	Py_Finalize();
}


void Interpreter::initialize(const wchar_t* dir)
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


void Interpreter::addToPath(const wchar_t* folder)
{
	Module os { ImportModule("os") };
	Object cwd{ os.CallFunction("getcwd") };
	std::wstring path{ Py_GetPath() + (L";" + cwd.ToString()) + folder };
	PySys_SetPath(path.c_str());
}
