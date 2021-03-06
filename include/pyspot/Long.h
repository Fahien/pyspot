#ifndef PST_LONG_H_
#define PST_LONG_H_

#include "pyspot/Object.h"

namespace pyspot
{

class Long : public Object
{
  public:
	Long(PyObject* object);
	Long(const Object& object);
	Long(const long l);
	~Long();

	long get_value() const;

	bool operator==(int i) const { return get_value() == i; }
};

}

#endif // PST_STRING_H_
