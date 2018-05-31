#include "pyspot/Tuple.h"

#include <cassert>

using namespace pyspot;


Tuple::Tuple(size_t size)
:	Object{ PyTuple_New(size) }
,	mSize{ size }
{}


Tuple::Tuple(std::initializer_list<Object*> list)
:	Tuple{ list.size() }
{
	size_t i{ 0 };
	for (const Object* o : list)
	{
		SetItem(i++, *o);
	}
}


void Tuple::SetItem(const size_t i, const Object& item)
{
	assert(i < mSize);

	Py_INCREF(item.GetObject());
	// Consume the item reference
	PyTuple_SetItem(mObject, i, item.GetObject());
}


void Tuple::SetItem(const size_t i, int item)
{
	SetItem(i, Py_BuildValue("i", item));
}


void Tuple::SetItem(const size_t i, unsigned item)
{
	SetItem(i, Py_BuildValue("I", item));
}


void Tuple::SetItem(const size_t i, float item)
{
	SetItem(i, Py_BuildValue("f", item));
}


void Tuple::SetItem(const size_t i, PyObject* item)
{
	assert(i < mSize);
	Py_INCREF(item);
	// Consume the item reference
	PyTuple_SetItem(mObject, i, item);
}
