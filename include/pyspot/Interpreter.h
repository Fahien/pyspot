#ifndef PST_INTERPRETER_H_
#define PST_INTERPRETER_H_

#include <string>
#include "pyspot/Module.h"

#include <Python.h>


namespace pyspot
{

class Interpreter
{
public:
	Interpreter();
	Interpreter(const wchar_t* dir);
	Interpreter(const std::wstring& dir);
	Interpreter(const char* import, PyObject* (*function)(void));
	Interpreter(const char* import, PyObject* (*function)(void), const wchar_t* dir);
	Interpreter(const char* import, PyObject* (*function)(void), const std::wstring& dir);
	~Interpreter();

	Module ImportModule(const char* name);
	Module ImportModule(const std::string& name);

private:
	void addToPath (const wchar_t* dir);

	void initialize(const wchar_t* dir);

	std::wstring mPath;
};

}

#endif // PST_INTERPRETER_H_
