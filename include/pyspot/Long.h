#ifndef PST_LONG_H_
#define PST_LONG_H_

#include "pyspot/Object.h"

namespace pyspot
{

class Long : public Object
{
  public:
	Long(PyObject* object);
	Long(const long l);
	~Long();
};

}

#endif // PST_STRING_H_
