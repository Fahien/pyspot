#ifndef PST_PYSPOTMODULE_H
#define PST_PYSPOTMODULE_H

#include <PySpotString.h>


namespace pyspot
{

class PySpotModule : public PySpotObject
{
public:
	PySpotModule(const PySpotString& name);
	~PySpotModule();

	PySpotObject CallFunction(const char* name);
	PySpotObject CallFunction(const char* name, PyObject* args);
};

}

#endif // PST_PYSPOTMODULE_H
