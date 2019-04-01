#include "pyspot/Dictionary.h"

namespace pyspot
{


Dictionary::Dictionary()
:	Object{ PyDict_New() }
{}


Dictionary::Dictionary( PyObject* o )
:	Object{ o }
{
	assert( PyDict_Check( object ) && "Object must be a dictionary");
}


Dictionary::Dictionary( const Object& other )
:	Object{ ( PyDict_Check( other.GetObject() ), other.GetIncref() ) }
{}


Dictionary::~Dictionary()
{
	PyDict_Clear( object );
}


void Dictionary::SetItem( const char* key, Object& val )
{
	PyDict_SetItemString( object, key, val.GetObject() );
}


void Dictionary::SetItem( const std::string& key, Object& val )
{
	SetItem( key.c_str(), val );
}


void Dictionary::SetItem( const Object& key, Object& val )
{
	PyDict_SetItem( object, key.GetObject(), val.GetObject() );
}


} // namespace pyspot
