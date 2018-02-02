#ifndef PST_PYSPOTTUPLE_H_
#define PST_PYSPOTTUPLE_H_

#include "PySpotObject.h"

#include <initializer_list>


namespace pyspot
{


class PySpotTuple : public PySpotObject
{
public:
	PySpotTuple(size_t size);
	PySpotTuple(std::initializer_list<PySpotObject*> list);

	inline size_t GetSize() const { return mSize; }

	void SetItem(const size_t i, int item);
	void SetItem(const size_t i, unsigned item);
	void SetItem(const size_t i, float item);
	void SetItem(const size_t i, const PySpotObject& item);
	void SetItem(const size_t i, PyObject* item);

private:
	size_t mSize;
};


}


#endif // PST_PYSPOTTUPLE_H_
