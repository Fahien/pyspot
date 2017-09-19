#include <stdio.h>
#include <PySpotFunction.h>
#include <PySpotException.h>

using namespace pyspot;


PySpotFunction::PySpotFunction(const PySpotModule& module, const char* name)
{
	mObject = PyObject_GetAttrString(module.getObject(), name);
	if (!mObject || !PyCallable_Check(mObject))
	{
		throw PySpotException{ "Not a function" };
	}
	printf("PySpotFunction %p\n", mObject);
}


PySpotFunction::~PySpotFunction()
{
	printf("Destroying PySpotFunction %p\n", mObject);
}


PySpotObject PySpotFunction::call(const void* args)
{
	return PySpotObject{ PyObject_CallObject(mObject, nullptr) };
}
