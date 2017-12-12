#include <cstdio>
#include "PySpotFunction.h"
#include "PySpotException.h"
#include "PySpotModule.h"
#include "PySpotTuple.h"

namespace pst = pyspot;


pst::PySpotFunction::PySpotFunction(const pst::PySpotModule& module, const char* name)
{
	mObject = PyObject_GetAttrString(module.GetObject(), name);
	if (!mObject || !PyCallable_Check(mObject))
	{
		throw pst::PySpotException{ "Not a function" };
	}
	printf("PySpotFunction %p\n", mObject);
}


pst::PySpotFunction::~PySpotFunction()
{
	printf("Destroying PySpotFunction %p\n", mObject);
}


pst::PySpotObject pst::PySpotFunction::Call()
{
	return pst::PySpotObject{ PyObject_CallObject(mObject, nullptr) };
}


pst::PySpotObject pst::PySpotFunction::Call(pst::PySpotTuple& args)
{
	return pst::PySpotObject{ PyObject_CallObject(mObject, args.GetObject()) };
}
