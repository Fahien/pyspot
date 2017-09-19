#include <PySpotModule.h>
#include <PySpotFunction.h>

using namespace pyspot;


PySpotModule::PySpotModule(const PySpotString& name)
{
	mObject = PyImport_Import(name.getObject());
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


PySpotObject PySpotModule::callFunction(const char* name)
{
	PySpotFunction function{ *this, name };
	return function.call(nullptr);
}
