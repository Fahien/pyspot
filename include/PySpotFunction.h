#ifndef PST_PYSPOTFUNCTION_H
#define PST_PYSPOTFUNCTION_H

#include <PySpotModule.h>

namespace pyspot
{

class PySpotFunction : public PySpotObject
{
public:
	PySpotFunction(const PySpotModule& module, const char* name);
	~PySpotFunction();

	PySpotObject Call(PyObject* args);
};

}

#endif // PST_PYSPOTFUNCTION_H
