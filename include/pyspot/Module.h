#ifndef PST_MODULE_H_
#define PST_MODULE_H_

#include <map>
#include <string>

#include "pyspot/Object.h"
#include "pyspot/Method.h"
#include "pyspot/String.h"


namespace pyspot
{

class String;
class Tuple;


class Module : public Object
{
public:
	Module(const char* name);
	Module(const tstring& name);
	Module(const String& name);
	~Module();

	const std::string& GetName() const { return mName; }

	Object Invoke(const std::string& name);
	Object Invoke(const std::string& name, const Tuple& args);

private:
	const std::string mName;
	std::map<const std::string, Method> mMethods;
};


}


#endif // PST_MODULE_H_
