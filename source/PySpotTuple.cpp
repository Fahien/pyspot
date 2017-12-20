#include <cassert>
#include "PySpotTuple.h"


namespace pst = pyspot;


pst::PySpotTuple::PySpotTuple(size_t size)
:	pst::PySpotObject{ PyTuple_New(size) }
,	mSize{ size }
{}


pst::PySpotTuple::PySpotTuple(std::initializer_list<PySpotObject*> list)
:	pst::PySpotTuple{ list.size() }
{
	size_t i{ 0 };
	for (const PySpotObject* o : list)
	{
		SetItem(i++, *o);
	}
}


void pst::PySpotTuple::SetItem(const size_t i, const pst::PySpotObject& item)
{
	assert(i < mSize);

	Py_INCREF(item.GetObject());
	// Consume the item reference
	PyTuple_SetItem(mObject, i, item.GetObject());
}


void pst::PySpotTuple::SetItem(const size_t i, int item)
{
	SetItem(i, Py_BuildValue("i", item));
}


void pst::PySpotTuple::SetItem(const size_t i, float item)
{
	SetItem(i, Py_BuildValue("f", item));
}


void pst::PySpotTuple::SetItem(const size_t i, PyObject* item)
{
	assert(i < mSize);
	Py_INCREF(item);
	// Consume the item reference
	PyTuple_SetItem(mObject, i, item);
}
