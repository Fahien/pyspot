#include "pyspot/Bool.h"

#include <cassert>


namespace pyspot
{


Bool::Bool( Object&& o )
:	Object{ std::move( o ) }
,	value{ PyLong_AsLong( object ) == 1L }
{
	assert( PyBool_Check( object ) && "Object is not a Bool" );
}


Bool::Bool( const bool b )
:	Object{ PyBool_FromLong( static_cast<long>( b ) ) }
,	value { b }
{}


} // namespace pyspot
