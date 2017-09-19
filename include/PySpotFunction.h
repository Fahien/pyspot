#ifndef PST_PYSPOTFUNCTION_H
#define PST_PYSPOTFUNCTION_H

#include <stdio.h>
#include <PySpotModule.h>

namespace pyspot
{

class PySpotFunction : public PySpotObject
{
public:
	PySpotFunction(const PySpotModule& module, const char* name);
	~PySpotFunction();

	PySpotObject call(const void* args);
};

}

#endif // PST_PYSPOTFUNCTION_H
