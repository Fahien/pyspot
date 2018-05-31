#include "pyspot/Module.h"
#include "pyspot/Function.h"
#include "pyspot/String.h"
#include "pyspot/Tuple.h"

using namespace pyspot;


Module::Module(const String& name)
{
	mObject = PyImport_Import(name.GetObject());
	if (!mObject)
	{
		PyErr_Print();
	}
}


Module::~Module()
{}


Object Module::CallFunction(const std::string& name)
{
	auto pair = mFunctions.find(name);
	if (pair == mFunctions.end())
	{
		mFunctions[name] = Function{ *this, name };
		pair = mFunctions.find(name);
	}

	return pair->second.Call();
}


Object Module::CallFunction(const std::string& name, const Tuple& args)
{
	auto pair = mFunctions.find(name);
	if (pair == mFunctions.end())
	{
		mFunctions[name] = Function{ *this, name };
		pair = mFunctions.find(name);
	}

	return pair->second.Call(args);
}
