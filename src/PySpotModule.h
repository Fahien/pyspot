#ifndef PST_PYSPOTMODULE_H
#define PST_PYSPOTMODULE_H

#include <stdio.h>
#include "PySpotString.h"

namespace pyspot
{

class PySpotModule : public PySpotObject
{
public:
	PySpotModule(const PySpotString & name);
	~PySpotModule();

	PySpotObject callFunction(const char * name);
};

}

#endif // PST_PYSPOTMODULE_H
