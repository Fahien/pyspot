#include "pyspot/Bool.h"

#include <cassert>


namespace pyspot
{


Bool::Bool( Object&& object )
:	Object{ std::move( object ) }
,	value{ PyLong_AsLong( mObject ) == 1L }
{
	assert( PyBool_Check( mObject ) && "Object is not a Bool" );
}


Bool::Bool( const bool b )
:	Object{ PyBool_FromLong( static_cast<long>( b ) ) }
,	value { b }
{}


} // namespace pyspot
