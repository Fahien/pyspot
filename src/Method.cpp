#include "pyspot/Method.h"

#include <cstdio>
#include <string>

#include "pyspot/Exception.h"
#include "pyspot/Module.h"
#include "pyspot/Tuple.h"


namespace pyspot
{


Method::Method(const Module& module, const std::string& name)
:	Object{ PyObject_GetAttrString(module.GetObject(), name.c_str()) }
,	mName{ name }
{
	if (!mObject || !PyCallable_Check(mObject))
	{
		throw Exception{ _T("Not a method") };
	}
}



Method::Method(const Module& module, const String& name)
:	Object{ PyObject_GetAttr(module.GetObject(), name.GetObject()) }
,	mName{ name.ToString() }
{
	if (!mObject || !PyCallable_Check(mObject))
	{
		throw Exception{ _T("Not a method") };
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


} // namespace pyspot
