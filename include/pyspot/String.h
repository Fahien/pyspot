#ifndef PST_STRING_H_
#define PST_STRING_H_

#include "pyspot/Object.h"

namespace pyspot
{

class String : public Object
{
  public:
	String(PyObject* object);
	String(const Object& object);
	String(const std::string& str);
	String(const std::wstring& str);
	~String();

  private:
	const std::string  mStr;
	const std::wstring mWStr;

	friend bool operator==(const String&, const std::string&);
};


inline bool operator==(const String& lhs, const std::string& rhs)
{
	return lhs.mStr == rhs;
}


}


#endif // PST_STRING_H_
