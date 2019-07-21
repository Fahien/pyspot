#include "pyspot/Method.h"

#include <cstdio>
#include <string>

#include "pyspot/Exception.h"
#include "pyspot/Module.h"

namespace pyspot
{
Method::Method( const Module& module, const std::string& n )
    : Object{ PyObject_GetAttrString( module.GetObject(), n.c_str() ) }, name{ n }
{
	if ( !object || !PyCallable_Check( object ) )
	{
		auto nam = std::wstring{ std::begin( name ), std::end( name ) };
		auto msg = L"Not a method: " + nam;
		throw Exception{ msg };
	}
}


Method::Method( const Module& module, const String& n )
    : Object{ PyObject_GetAttr( module.GetObject(), n.GetObject() ) }, name{ n.ToString() }
{
	if ( !object || !PyCallable_Check( object ) )
	{
		throw Exception{ _T("Not a method") };
	}
}


Object Method::call() const { return PyObject_CallObject( object, nullptr ); }


Object Method::call( const Tuple& args ) const { return PyObject_CallObject( object, args.GetObject() ); }


}  // namespace pyspot
