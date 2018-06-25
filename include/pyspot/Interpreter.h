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
	Interpreter(const char* dir);
	Interpreter(const std::string& dir);
	Interpreter(const char* import, void (*function)(void));
	Interpreter(const char* import, void (*function)(void), const char* dir);
	Interpreter(const char* import, void (*function)(void), const std::string& dir);
	~Interpreter();

	Module ImportModule(const char* name);
	Module ImportModule(const std::string& name);

private:
	void addToPath (const char* dir);

	void initialize(const char* dir);

	std::string mPath;
};

}

#endif // PST_INTERPRETER_H_
