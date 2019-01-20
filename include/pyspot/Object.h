#ifndef PST_OBJECT_H_
#define PST_OBJECT_H_

#include <Python.h>
#include <string>

#include "pyspot/common.h"

namespace pyspot
{


class Object
{
public:
	Object();
	Object(PyObject* object);
	virtual ~Object();

	Object(const Object& other);
	Object(Object&& other);

	Object& operator=(const Object& other);
	Object& operator=(Object&& other);

	PyObject* GetObject() const { return mObject; }
	PyObject* GetIncref() const { Py_INCREF(mObject); return mObject; }

	#if PY_MAJOR_VERSION >= 3
	const char*    ToCString()  const { return PyUnicode_AsUTF8(mObject); }
	const wchar_t* ToWCString() const { return PyUnicode_AsUnicode(mObject); }
	#else
	const char*    ToCString()  const { return PyString_AsString(mObject); }
	const wchar_t* ToWCString() const { return L""; }
	#endif
	std::string    ToString()   const { return ToCString(); }
	std::wstring   ToWString()  const { return ToWCString(); }
	tstring ToTString() const;

protected:
	PyObject* mObject;
};

}

#endif // PST_OBJECT_H_
