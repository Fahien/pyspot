#include <cstdio>
#include <PySpotFunction.h>
#include <PySpotException.h>

using namespace pyspot;


PySpotFunction::PySpotFunction(const PySpotModule& module, const char* name)
{
	mObject = PyObject_GetAttrString(module.GetObject(), name);
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


PySpotObject PySpotFunction::Call(PyObject* args)
{
	return PySpotObject{ PyObject_CallObject(mObject, args) };
}
