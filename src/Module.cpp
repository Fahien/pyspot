#include "pyspot/Module.h"
#include "pyspot/Method.h"
#include "pyspot/String.h"
#include "pyspot/Tuple.h"
#include "pyspot/Exception.h"
#include "pyspot/Error.h"

using namespace pyspot;


Module::Module(const char* name)
:	Object{ PyImport_ImportModule(name) }
,	mName{ name }
{
	Error::Check();
}


Module::Module(const string& name)
:	Module{ String{ name } }
{}


Module::Module(const String& name)
:	Object{ PyImport_Import(name.GetObject()) }
,	mName{ name.ToString() }
{
	Error::Check();
}


Module::~Module()
{}


Object Module::Invoke(const std::string& name)
{
	auto pair = mMethods.find(name);
	if (pair == mMethods.end())
	{
		mMethods.emplace(name, Method{ *this, name });
		pair = mMethods.find(name);
	}

	return pair->second.Invoke();
}


Object Module::Invoke(const std::string& name, const Tuple& args)
{
	auto pair = mMethods.find(name);
	if (pair == mMethods.end())
	{
		mMethods.emplace(name, Method{ *this, name });
		pair = mMethods.find(name);
	}

	return pair->second.Invoke(args);
}
