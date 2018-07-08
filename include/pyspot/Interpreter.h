#ifndef PST_INTERPRETER_H_
#define PST_INTERPRETER_H_

#include <string>
#include <Python.h>

#include "pyspot/common.h"


namespace pyspot
{

class Interpreter
{
public:
	Interpreter(const string& dir = _T("script"));
	Interpreter(const char* import, init_f function, const string& dir = _T("script"));
	~Interpreter();

private:
	void addToPath (const string& dir);

	void initialize(const string& dir);

	string mPath;
};

}

#endif // PST_INTERPRETER_H_
