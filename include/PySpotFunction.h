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
	PySpotFunction();
	PySpotFunction(const PySpotModule& module, const std::string& name);
	~PySpotFunction();

	PySpotObject Call() const;
	PySpotObject Call(const PySpotTuple& args) const;
};


}


#endif // PST_PYSPOTFUNCTION_H
