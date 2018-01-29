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


pst::PySpotObject pst::PySpotModule::CallFunction(const std::string& name)
{
	auto pair = mFunctions.find(name);
	if (pair == mFunctions.end())
	{
		mFunctions[name] = pst::PySpotFunction{ *this, name };
		pair = mFunctions.find(name);
	}

	return pair->second.Call();
}


pst::PySpotObject pst::PySpotModule::CallFunction(const std::string& name, const pst::PySpotTuple& args)
{
	auto pair = mFunctions.find(name);
	if (pair == mFunctions.end())
	{
		mFunctions[name] = pst::PySpotFunction{ *this, name };
		pair = mFunctions.find(name);
	}

	return pair->second.Call(args);
}
