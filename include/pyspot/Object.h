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
	~Object();

	Object(const Object&  other);
	Object(const Object&& other);

	Object& operator=(const Object& other);
	Object& operator=(Object&& other);

	PyObject* GetObject() const { return mObject; }
	PyObject* GetIncref() const { Py_INCREF(mObject); return mObject; }

	#if PYTHON_VERSION >= 3
	const char*    ToCString()  const { return PyUnicode_AS_DATA(mObject); }
	const wchar_t* ToWCString() const { return PyUnicode_AS_UNICODE(mObject); }
	#else
	const char*    ToCString()  const { return PyString_AS_STRING(mObject); }
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
