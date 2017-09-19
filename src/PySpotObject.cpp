#include <PySpotObject.h>

using namespace pyspot;


PySpotObject::PySpotObject()
{}


PySpotObject::PySpotObject(PyObject* object)
:	mObject{ object }
{}


PySpotObject::~PySpotObject()
{
	if (mObject)
	{
		printf("Destroying PyObject %p\n", mObject);
		Py_DECREF(mObject);
	}
}


PySpotObject::PySpotObject(const PySpotObject& other)
:	mObject{ other.mObject }
{
	printf("Copied PyObject %p\n", other.mObject);
}


PySpotObject& PySpotObject::operator=(const PySpotObject& other)
{
	mObject = other.mObject;
	printf("Assigned PyObject %p %p\n", mObject, other.mObject);
	return *this;
}
