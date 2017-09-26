#ifndef PST_PYSPOTFUNCTION_H
#define PST_PYSPOTFUNCTION_H

#include "PySpotObject.h"

namespace pyspot
{


class PySpotModule;
class PySpotTuple;


class PySpotFunction : public PySpotObject
{
public:
	PySpotFunction(const PySpotModule& module, const char* name);
	~PySpotFunction();

	PySpotObject Call();
	PySpotObject Call(PySpotTuple& args);
};


}


#endif // PST_PYSPOTFUNCTION_H
