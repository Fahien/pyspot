#include "pyspot/Function.h"
#include "pyspot/Exception.h"
#include "pyspot/Module.h"
#include "pyspot/Tuple.h"

#include <cstdio>
#include <string>

using namespace pyspot;


Function::Function() {}


Function::Function(const Module& module, const std::string& name)
:   Object{ PyObject_GetAttrString(module.GetObject(), name.c_str()) }
{
	if (!mObject || !PyCallable_Check(mObject))
	{
		throw Exception{ "Not a function" };
	}
}


Function::~Function()
{}


Object Function::Call() const
{
	return PyObject_CallObject(mObject, nullptr);
}


Object Function::Call(const Tuple& args) const
{
	return PyObject_CallObject(mObject, args.GetObject());
}
