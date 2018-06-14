#ifndef PST_MODULE_H_
#define PST_MODULE_H_

#include "pyspot/Object.h"
#include "pyspot/Function.h"

#include <map>
#include <string>

namespace pyspot
{


class String;
class Tuple;


class Module : public Object
{
public:
	Module(const char* name);
	Module(const String& name);
	~Module();

	Object CallFunction(const std::string& name);
	Object CallFunction(const std::string& name, const Tuple& args);

private:
	std::map<const std::string, Function> mFunctions;
};


}


#endif // PST_MODULE_H_
