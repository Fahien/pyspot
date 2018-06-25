#ifndef PST_STRING_H_
#define PST_STRING_H_

#include "Object.h"

namespace pyspot
{

class String : public Object
{
  public:
	String(PyObject* object);
	String(const std::string& str);
	String(const char* str);
	~String();

	const char* ToCString() const { return mCStr; }

  private:
	const char* mCStr;
};

}

#endif // PST_STRING_H_
