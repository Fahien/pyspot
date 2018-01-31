#ifndef PST_PYSPOTFUNCTION_H_
#define PST_PYSPOTFUNCTION_H_

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


#endif // PST_PYSPOTFUNCTION_H_
