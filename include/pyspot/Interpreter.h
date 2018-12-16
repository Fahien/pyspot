#ifndef PST_INTERPRETER_H_
#define PST_INTERPRETER_H_

#include <string>
#include <Python.h>

#include "pyspot/Common.h"


namespace pyspot
{

class Interpreter
{
public:
	Interpreter(const tstring& dir = _T("script"));
	Interpreter(const char* import, init_f function, const tstring& dir = _T("script"));
	~Interpreter();

private:
	void addToPath (const tstring& dir);

	void initialize(const tstring& dir);

	tstring mPath;
};

}

#endif // PST_INTERPRETER_H_
