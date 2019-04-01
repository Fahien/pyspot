#include "pyspot/Tuple.h"


namespace pyspot
{


Tuple::Tuple( PyObject* o )
:	Object{ o }
,	m_Size { static_cast<size_t>( PyTuple_Size( object ) ) }
{
	assert( PyTuple_Check( object ) && "Object must be a tuple");
}


Tuple::Tuple( const size_t size )
:	Object{ PyTuple_New( size ) }
,	m_Size { size }
{}


Tuple::Tuple( std::initializer_list<Object> list )
:	Tuple{ list.size() }
{
	size_t i { 0 };
	for ( const auto& o : list )
	{
		SetItem( i++, o );
	}
}


void Tuple::SetItem( const size_t i, const Object& item )
{
	assert( i < m_Size && "Index must be less than tuple size" );

	// Consume the item reference
	PyTuple_SetItem( object, i, item.GetIncref() );
}


void Tuple::SetItem( const size_t i, int item )
{
	SetItem( i, Py_BuildValue( "i", item ) );
}


void Tuple::SetItem( const size_t i, unsigned item )
{
	SetItem( i, Py_BuildValue( "I", item ) );
}


void Tuple::SetItem( const size_t i, float item )
{
	SetItem( i, Py_BuildValue( "f", item ) );
}


void Tuple::SetItem( const size_t i, PyObject* item )
{
	assert( i < m_Size && "Index must be less than tuple size" );

	Py_INCREF( item );
	// Consume the item reference
	PyTuple_SetItem( object, i, item );
}


} // namespace pyspot
