#ifndef PST_METHOD_H_
#define PST_METHOD_H_

#include "pyspot/Object.h"

namespace pyspot
{


class Module;
class Tuple;


class Method : public Object
{
public:
	Method();
	Method(const Module& module, const std::string& name);
	~Method();

	Object Invoke() const;
	Object Invoke(const Tuple& args) const;
};


}


#endif // PST_METHOD_H_
