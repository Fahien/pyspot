#include "pyspot/Method.h"

#include <cstdio>
#include <string>

#include "pyspot/Exception.h"
#include "pyspot/Module.h"

namespace pyspot
{
Method::Method( const Module& module, const std::string& name )
    : Object{ PyObject_GetAttrString( module.GetObject(), name.c_str() ) }, mName{ name }
{
	if ( !object || !PyCallable_Check( object ) )
	{
		auto nam = std::wstring{ std::begin( name ), std::end( name ) };
		auto msg = L"Not a method: " + nam;
		throw Exception{ msg };
	}
}


Method::Method( const Module& module, const String& name )
    : Object{ PyObject_GetAttr( module.GetObject(), name.GetObject() ) }, mName{ name.ToString() }
{
	if ( !object || !PyCallable_Check( object ) )
	{
		throw Exception{ _T("Not a method") };
	}
}


Object Method::Invoke() const { return PyObject_CallObject( object, nullptr ); }


Object Method::Invoke( const Tuple& args ) const { return PyObject_CallObject( object, args.GetObject() ); }


}  // namespace pyspot
