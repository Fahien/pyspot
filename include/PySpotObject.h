#ifndef PST_PYSPOTOBJECT_H_
#define PST_PYSPOTOBJECT_H_

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

	PySpotObject(const PySpotObject&  other);
	PySpotObject(const PySpotObject&& other);

	PySpotObject& operator=(const PySpotObject&  other);
	PySpotObject& operator=(PySpotObject&& other);

	PyObject* GetObject() const { return mObject; }
	PyObject* GetIncref() const { Py_INCREF(mObject); return mObject; }

	const wchar_t* ToCString() const { return PyUnicode_AS_UNICODE(mObject); }
	std::wstring   ToString()  const { return ToCString(); }

protected:
	PyObject* mObject;
};

}

#endif // PST_PYSPOTOBJECT_H_
