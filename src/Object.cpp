#include "pyspot/Object.h"


namespace pyspot
{


Object::Object()
:	object { nullptr }
{}


Object::Object( PyObject* object )
:	object { object }
{}


Object::~Object()
{
	Py_XDECREF( object );
}


Object::Object(const Object& other)
:	object{ other.object }
{
	Py_XINCREF( object );
}


Object::Object(Object&& other)
:	object{ other.object }
{
	other.object = nullptr;
}


Object& Object::operator=(const Object& other)
{
	if ( this != &other )
	{
		if ( object != other.object )
		{
			Py_XDECREF( object );

			object = other.object;
		}

		Py_XINCREF( object );
	}

	return *this;
}


Object& Object::operator=( Object&& other )
{
	if ( this != &other )
	{
		if ( object != other.object )
		{
			Py_XDECREF( object );

			object = other.object;
		}

		other.object = nullptr;
	}

	return *this;
}


tstring Object::ToTString() const
{
	#if PY_MAJOR_VERSION >= 3
	return ToWString();
	#else
	return ToString();
	#endif
}


} // namespace pyspot
