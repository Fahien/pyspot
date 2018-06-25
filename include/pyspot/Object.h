#ifndef PST_OBJECT_H_
#define PST_OBJECT_H_

#include <Python.h>
#include <string>

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

	const char* ToCString() const { return PyString_AsString(mObject); }
	std::string ToString()  const { return ToCString(); }

protected:
	PyObject* mObject;
};

}

#endif // PST_OBJECT_H_
