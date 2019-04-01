#ifndef PYSPOT_TUPLE_H_
#define PYSPOT_TUPLE_H_

#include <initializer_list>

#include "pyspot/Object.h"


namespace pyspot
{
class Tuple : public Object
{
  public:
	Tuple( PyObject* pObject );
	Tuple( const size_t size );
	Tuple( std::initializer_list<Object> list );

	inline size_t GetSize() const { return m_Size; }

	void SetItem( const size_t i, int item );
	void SetItem( const size_t i, unsigned item );
	void SetItem( const size_t i, float item );
	void SetItem( const size_t i, const Object& item );
	void SetItem( const size_t i, PyObject* pItem );

  private:
	size_t m_Size;
};


}  // namespace pyspot

#endif  // PYSPOT_TUPLE_H_
