#ifndef PST_PYSPOT_H_
#define PST_PYSPOT_H_

#include <string>
#include "PySpotModule.h"

#include <Python.h>


namespace pyspot
{

class PySpot
{
public:
	PySpot();
	PySpot(const wchar_t* dir);
	PySpot(const std::wstring& dir);
	PySpot(const char* import, PyObject* (*function)(void));
	PySpot(const char* import, PyObject* (*function)(void), const wchar_t* dir);
	PySpot(const char* import, PyObject* (*function)(void), const std::wstring& dir);
	~PySpot();

	PySpotModule ImportModule(const char* name);
	PySpotModule ImportModule(const std::string& name);

private:
	void addToPath (const wchar_t* dir);

	void initialize(const wchar_t* dir);

	std::wstring mPath;
};

}

#endif // PST_PYSPOT_H_
