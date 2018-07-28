#include "pyspot/Object.h"

using namespace pyspot;


Object::Object()
:	mObject{ nullptr }
{}


Object::Object(PyObject* object)
:	mObject{ object }
{}


Object::~Object()
{
	Py_XDECREF(mObject);
}


Object::Object(const Object& other)
:	mObject{ other.mObject }
{
	Py_XINCREF(mObject);
}


Object::Object(const Object&& other)
: mObject{ other.mObject }
{}


Object& Object::operator=(const Object& other)
{
	if (this != &other)
	{
		if (mObject != other.mObject)
		{
			Py_XDECREF(mObject);

			mObject = other.mObject;
		}

		Py_XINCREF(mObject);
	}

	return *this;
}


Object& Object::operator=(Object&& other)
{
	if (this != &other)
	{
		if (mObject != other.mObject)
		{
			Py_XDECREF(mObject);

			mObject = other.mObject;
		}

		other.mObject = nullptr;
	}

	return *this;
}


tstring Object::ToTString() const
{
	#if PYTHON_VERSION >= 3
	return ToWString();
	#else
	return ToString();
	#endif
}
