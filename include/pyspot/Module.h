#ifndef PST_MODULE_H_
#define PST_MODULE_H_

#include <map>
#include <string>

#include "pyspot/Method.h"
#include "pyspot/Object.h"
#include "pyspot/String.h"


namespace pyspot
{
class String;
class Tuple;


class Module : public Object
{
  public:
	Module( PyObject* module, const char* name );
	Module( const char* name );
	Module( const tstring& name );
	Module( const String& name );
	~Module() = default;

	const std::string& get_name() const { return name; }

	Method* get_method( const std::string& name );

	Object call( const std::string& name );
	Object call( const std::string& name, const Tuple& args );

  private:
	const std::string                   name;
	std::map<const std::string, Method> methods;
};


}  // namespace pyspot


#endif  // PST_MODULE_H_
