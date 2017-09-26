#include <cassert>
#include "PySpotTuple.h"


namespace pst = pyspot;


pst::PySpotTuple::PySpotTuple(size_t size)
:	pst::PySpotObject{ PyTuple_New(size) }
,	mSize{ size }
{}


void pst::PySpotTuple::SetItem(const size_t i, pst::PySpotObject& item)
{
	assert(i < mSize);

	Py_INCREF(item.GetObject());
	// Consume the item reference
	PyTuple_SetItem(mObject, i, item.GetObject());
}
