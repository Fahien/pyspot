#ifndef PST_PYSPOT_H
#define PST_PYSPOT_H

#include "PySpotModule.h"

namespace pyspot
{

class PySpot
{
public:
	PySpot();
	~PySpot();

	PySpotModule importModule(const char * name);
};

}

#endif // PST_PYSPOT_H