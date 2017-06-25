#include "PySpotObject.h"

using namespace pyspot;


PySpotObject::PySpotObject()
{}


PySpotObject::PySpotObject(PyObject * object)
	: object_{ object }
{}


PySpotObject::~PySpotObject()
{
	if (object_)
	{
		printf("Destroying PyObject %p\n", object_);
		Py_DECREF(object_);
	}
}


PySpotObject::PySpotObject(const PySpotObject & other)
	: object_{ other.object_ }
{
	printf("Copied PyObject %p\n", other.object_);
}


PySpotObject & PySpotObject::operator=(const PySpotObject & other)
{
	object_ = other.object_;
	printf("Assigned PyObject %p %p\n", object_, other.object_);
	return *this;
}
