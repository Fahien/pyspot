#ifndef PST_METHOD_H_
#define PST_METHOD_H_

#include "pyspot/Object.h"
#include "pyspot/String.h"
#include "pyspot/Tuple.h"

namespace pyspot
{


class Module;
class Tuple;


class Method : public Object
{
public:
	Method(const Module& module, const std::string& name);
	Method(const Module& module, const String& name);

	const std::string& GetName() const { return mName; }

	Object Invoke() const;
	Object Invoke(const Tuple& args) const;

private:
	const std::string mName;
};


}


#endif // PST_METHOD_H_
