#ifndef PST_PYSPOTMODULE_H
#define PST_PYSPOTMODULE_H

#include "PySpotObject.h"


namespace pyspot
{


class PySpotString;
class PySpotTuple;


class PySpotModule : public PySpotObject
{
public:
	PySpotModule(const PySpotString& name);
	~PySpotModule();

	PySpotObject CallFunction(const char* name);
	PySpotObject CallFunction(const char* name, PySpotTuple& args);
};


}


#endif // PST_PYSPOTMODULE_H
