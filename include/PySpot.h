#ifndef PST_PYSPOT_H
#define PST_PYSPOT_H

#include <string>
#include <Python.h>
#include <PySpotModule.h>


namespace pyspot
{

class PySpot
{
public:
	PySpot();
	PySpot(const wchar_t* dir);
	PySpot(const char* import, PyObject* (*function)(void));
	PySpot(const char* import, PyObject* (*function)(void), const wchar_t* dir);
	~PySpot();

	PySpotModule ImportModule(const char* name);

private:
	void addToPath (const wchar_t* dir);

	void initialize(const wchar_t* dir);

	std::wstring mPath;
};

}

#endif // PST_PYSPOT_H
