#include "pyspot/Module.h"

#include "pyspot/Method.h"
#include "pyspot/String.h"
#include "pyspot/Tuple.h"
#include "pyspot/Exception.h"
#include "pyspot/Error.h"


namespace pyspot
{


Module::Module( PyObject* module, const char* n )
:	Object{ module }
,	name { n }
{}


Module::Module( const char* n )
:	Object{ PyImport_ImportModule( n ) }
,	name{ n }
{
	Error::Check();
}


Module::Module( const tstring& n )
:	Module{ String{ n } }
{}


Module::Module( const String& n )
:	Object{ PyImport_Import( n.GetObject() ) }
,	name{ n.ToString() }
{
	Error::Check();
}


Module::~Module()
{}


Object Module::Invoke( const std::string& name )
{
	auto pair = methods.find( name );
	if ( pair == methods.end() )
	{
		methods.emplace( name, Method{ *this, name } );
		pair = methods.find( name );
	}

	return pair->second.Invoke();
}


Object Module::Invoke( const std::string& name, const Tuple& args )
{
	auto pair = methods.find( name );
	if ( pair == methods.end() )
	{
		methods.emplace( name, Method{ *this, name } );
		pair = methods.find( name );
	}

	auto ret = pair->second.Invoke( args );
#ifndef NDEBUG
	Error::Check();
#endif
	return ret;
}


} // namespace pyspot
