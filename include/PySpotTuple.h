#ifndef PST_PYSPOTTUPLE_H
#define PST_PYSPOTTUPLE_H

#include "PySpotObject.h"


namespace pyspot
{


class PySpotTuple : public PySpotObject
{
public:
	PySpotTuple(size_t size);

	inline size_t GetSize() const { return mSize; }

	void SetItem(const size_t i, int item);
	void SetItem(const size_t i, float item);
	void SetItem(const size_t i, PySpotObject& item);
	void SetItem(const size_t i, PyObject* item);

private:
	size_t mSize;
};


}


#endif // PST_PYSPOTTUPLE_H
