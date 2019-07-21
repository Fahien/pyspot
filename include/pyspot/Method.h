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
	Method( const Module& module, const std::string& name );
	Method( const Module& module, const String& name );

	const std::string& get_name() const { return name; }

	Object call() const;
	Object call( const Tuple& args ) const;

  private:
	const std::string name;
};


}  // namespace pyspot


#endif  // PST_METHOD_H_
