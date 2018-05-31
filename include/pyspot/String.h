#ifndef PST_STRING_H_
#define PST_STRING_H_

#include "Object.h"

namespace pyspot
{

class String : public Object
{
  public:
	String(PyObject* object);
	String(const char* str);
	~String();
};

}

#endif // PST_STRING_H_
