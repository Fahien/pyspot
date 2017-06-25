#include "PySpotModule.h"
#include "PySpotFunction.h"

using namespace pyspot;


PySpotModule::PySpotModule(const PySpotString & name)
{
	object_ = PyImport_Import(name.getObject());
	if (!object_)
	{
		PyErr_Print();
	}
	printf("Imported PySpotModule %p\n", object_);
}


PySpotModule::~PySpotModule()
{
	printf("Destroying PySpotModule %p\n", object_);
}


PySpotObject PySpotModule::callFunction(const char * name)
{
	PySpotFunction function{ *this, name };
	return function.call(nullptr);
}
