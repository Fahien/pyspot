#include "PySpotFunction.h"
#include "PySpotException.h"
#include "PySpotModule.h"
#include "PySpotTuple.h"

#include <cstdio>
#include <string>

namespace pst = pyspot;


pst::PySpotFunction::PySpotFunction() {}


pst::PySpotFunction::PySpotFunction(const pst::PySpotModule& module, const std::string& name)
{
	mObject = PyObject_GetAttrString(module.GetObject(), name.c_str());
	if (!mObject || !PyCallable_Check(mObject))
	{
		throw pst::PySpotException{ "Not a function" };
	}
}


pst::PySpotFunction::~PySpotFunction()
{}


pst::PySpotObject pst::PySpotFunction::Call() const
{
	return pst::PySpotObject{ PyObject_CallObject(mObject, nullptr) };
}


pst::PySpotObject pst::PySpotFunction::Call(const pst::PySpotTuple& args) const
{
	return pst::PySpotObject{ PyObject_CallObject(mObject, args.GetObject()) };
}
