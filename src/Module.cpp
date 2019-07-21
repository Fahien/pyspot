#include "pyspot/Module.h"

#include "pyspot/Error.h"
#include "pyspot/Exception.h"
#include "pyspot/Method.h"
#include "pyspot/String.h"
#include "pyspot/Tuple.h"


namespace pyspot
{
Module::Module( PyObject* module, const char* n ) : Object{ module }, name{ n } {}


Module::Module( const char* n ) : Object{ PyImport_ImportModule( n ) }, name{ n } { Error::Check(); }


Module::Module( const tstring& n ) : Module{ String{ n } } {}


Module::Module( const String& n ) : Object{ PyImport_Import( n.GetObject() ) }, name{ n.ToString() } { Error::Check(); }


Method* Module::get_method( const std::string& name )
{
	// Check if cached
	auto pair = methods.find( name );
	if ( pair != methods.end() )
	{
		return &pair->second;
	}

	// Construct and cache
	if ( PyObject_HasAttrString( object, name.c_str() ) )
	{
		auto method = PyObject_GetAttrString( object, name.c_str() );
		if ( method && PyCallable_Check( method ) )
		{
			auto [pair, ok] = methods.emplace( name, Method{ *this, name } );
			if ( ok )
			{
				return &pair->second;
			}
		}
	}

	// Not found
	return nullptr;
}


Object Module::call( const std::string& name ) { return get_method( name )->call(); }


Object Module::call( const std::string& name, const Tuple& args )
{
	auto ret = get_method( name )->call( args );
#ifndef NDEBUG
	Error::Check();
#endif
	return ret;
}


}  // namespace pyspot
