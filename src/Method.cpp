#include "pyspot/Method.h"
#include "pyspot/Exception.h"
#include "pyspot/Module.h"
#include "pyspot/Tuple.h"

#include <cstdio>
#include <string>

using namespace pyspot;


Method::Method() {}


Method::Method(const Module& module, const std::string& name)
:   Object{ PyObject_GetAttrString(module.GetObject(), name.c_str()) }
{
	if (!mObject || !PyCallable_Check(mObject))
	{
		throw Exception{ "Not a method" };
	}
}


Method::~Method()
{}


Object Method::Invoke() const
{
	return PyObject_CallObject(mObject, nullptr);
}


Object Method::Invoke(const Tuple& args) const
{
	return PyObject_CallObject(mObject, args.GetObject());
}
