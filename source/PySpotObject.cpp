#include "PySpotObject.h"

using namespace pyspot;


PySpotObject::PySpotObject()
:	mObject{ nullptr }
{}


PySpotObject::PySpotObject(PyObject* object)
:	mObject{ object }
{}


PySpotObject::~PySpotObject()
{
	Py_XDECREF(mObject);
}


PySpotObject::PySpotObject(const PySpotObject& other)
:	mObject{ other.mObject }
{
	Py_XINCREF(mObject);
}


PySpotObject::PySpotObject(const PySpotObject&& other)
: mObject{ other.mObject }
{}


PySpotObject& PySpotObject::operator=(const PySpotObject& other)
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


PySpotObject& PySpotObject::operator=(PySpotObject&& other)
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
