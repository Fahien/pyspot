#ifndef PST_TUPLE_H_
#define PST_TUPLE_H_

#include "Object.h"

#include <initializer_list>


namespace pyspot
{


class Tuple : public Object
{
public:
	Tuple(size_t size);
	Tuple(std::initializer_list<Object> list);

	inline size_t GetSize() const { return mSize; }

	void SetItem(const size_t i, int item);
	void SetItem(const size_t i, unsigned item);
	void SetItem(const size_t i, float item);
	void SetItem(const size_t i, const Object& item);
	void SetItem(const size_t i, PyObject* item);

private:
	size_t mSize;
};


}


#endif // PST_TUPLE_H_
