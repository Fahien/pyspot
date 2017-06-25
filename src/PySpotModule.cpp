#include "PySpotModule.h"

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
