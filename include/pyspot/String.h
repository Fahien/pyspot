#ifndef PST_STRING_H_
#define PST_STRING_H_

#include "pyspot/Object.h"

namespace pyspot
{

class String : public Object
{
  public:
	String(PyObject* object);
	String(const std::string& str);
	String(const char* str);
	~String();

	std::string ToString() const { return mStr; }
	const char* ToCString() const { return mStr.c_str(); }

  private:
	const std::string mStr;
};

}

#endif // PST_STRING_H_
