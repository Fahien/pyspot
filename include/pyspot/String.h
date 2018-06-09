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

	const wchar_t* ToCString() const { return mCStr; }

  private:
	const wchar_t* mCStr;
};

}

#endif // PST_STRING_H_
