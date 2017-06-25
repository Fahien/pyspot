#ifndef PST_PYSPOTMODULE_H
#define PST_PYSPOTMODULE_H

#include <stdio.h>
#include <Python.h>
#include "PySpotString.h"

namespace pyspot
{

class PySpotModule : public PySpotObject
{
public:
	PySpotModule(const PySpotString & name);
	~PySpotModule();
};

}

#endif // PST_PYSPOTMODULE_H
