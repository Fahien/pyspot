#ifndef PST_PYSPOTOBJECT_H
#define PST_PYSPOTOBJECT_H

#include <Python.h>
#include <string>

namespace pyspot
{

class PySpotObject
{
public:
	PySpotObject();
	PySpotObject(PyObject* object);
	~PySpotObject();

	PySpotObject(const PySpotObject& other);
	PySpotObject& operator=(const PySpotObject& other);

	PyObject* GetObject() const { return mObject; }

	const wchar_t* ToCString() const { return PyUnicode_AS_UNICODE(mObject); }
	std::wstring   ToString()  const { return ToCString(); }

protected:
	PyObject* mObject;
};

}

#endif // PST_PYSPOTOBJECT_H
