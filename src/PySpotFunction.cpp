#include <stdio.h>
#include "PySpotFunction.h"
#include "PySpotException.h"

using namespace pyspot;


PySpotFunction::PySpotFunction(const PySpotModule & module, const char * name)
{
	object_ = PyObject_GetAttrString(module.getObject(), name);
	if (!object_ || !PyCallable_Check(object_))
	{
		throw PySpotException{ "Not a function" };
	}
	printf("PySpotFunction %p\n", object_);
}


PySpotFunction::~PySpotFunction()
{
	printf("Destroying PySpotFunction %p\n", object_);
}


PySpotObject PySpotFunction::call(const void * args)
{
	return PySpotObject{ PyObject_CallObject(object_, nullptr) };
}
