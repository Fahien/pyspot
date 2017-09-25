#include <PySpotModule.h>
#include <PySpotFunction.h>

using namespace pyspot;


PySpotModule::PySpotModule(const PySpotString& name)
{
	mObject = PyImport_Import(name.GetObject());
	if (!mObject)
	{
		PyErr_Print();
	}
	printf("Imported PySpotModule %p\n", mObject);
}


PySpotModule::~PySpotModule()
{
	printf("Destroying PySpotModule %p\n", mObject);
}


PySpotObject PySpotModule::CallFunction(const char* name)
{
	return CallFunction(name, nullptr);
}


PySpotObject PySpotModule::CallFunction(const char* name, PyObject* args)
{
	PySpotFunction function{ *this, name };
	return function.Call(args);
}
