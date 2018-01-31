#ifndef PST_PYSPOTMODULE_H_
#define PST_PYSPOTMODULE_H_

#include "PySpotObject.h"
#include "PySpotFunction.h"

#include <map>
#include <string>

namespace pyspot
{


class PySpotString;
class PySpotTuple;


class PySpotModule : public PySpotObject
{
public:
	PySpotModule(const PySpotString& name);
	~PySpotModule();

	PySpotObject CallFunction(const std::string& name);
	PySpotObject CallFunction(const std::string& name, const PySpotTuple& args);

private:
	std::map<const std::string, PySpotFunction> mFunctions;
};


}


#endif // PST_PYSPOTMODULE_H_
