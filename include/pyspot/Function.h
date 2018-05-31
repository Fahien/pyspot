#ifndef PST_FUNCTION_H_
#define PST_FUNCTION_H_

#include "pyspot/Object.h"

namespace pyspot
{


class Module;
class Tuple;


class Function : public Object
{
public:
	Function();
	Function(const Module& module, const std::string& name);
	~Function();

	Object Call() const;
	Object Call(const Tuple& args) const;
};


}


#endif // PST_FUNCTION_H_
