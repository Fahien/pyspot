#include "PySpotModule.h"
#include "PySpotFunction.h"
#include "PySpotString.h"
#include "PySpotTuple.h"

namespace pst = pyspot;


pst::PySpotModule::PySpotModule(const pst::PySpotString& name)
{
	mObject = PyImport_Import(name.GetObject());
	if (!mObject)
	{
		PyErr_Print();
	}
	printf("Imported PySpotModule %p\n", mObject);
}


pst::PySpotModule::~PySpotModule()
{
	printf("Destroying PySpotModule %p\n", mObject);
}


pst::PySpotObject pst::PySpotModule::CallFunction(const char* name)
{
	pst::PySpotFunction function{ *this, name };
	return function.Call();
}


pst::PySpotObject pst::PySpotModule::CallFunction(const char* name, pst::PySpotTuple& args)
{
	pst::PySpotFunction function{ *this, name };
	return function.Call(args);
}
