#include "pyspot/Long.h"

#include <Python.h>
#include <cassert>


namespace pyspot
{
Long::Long( PyObject* o ) : Object{ o } { assert( PyLong_Check( object ) && "Object must be a Long" ); }


Long::Long( const Object& o ) : Object{ o } { assert( PyLong_Check( object ) && "Object must be a Long" ); }


Long::Long( const long l ) : Object{ PyLong_FromLong( l ) } {}


Long::~Long() {}


long Long::get_value() const { return PyLong_AsLong( object ); }

}  // namespace pyspot
