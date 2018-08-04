#ifndef WRAP_TEST_H_
#define WRAP_TEST_H_

#include <string>
#include <wrap/Person.h>


namespace wrap
{

class Test
{
  public:
	inline Test(const float v        = 0.0f,
	            const char* c        = "Arthur",
	            const std::string& n = "Ford",
	            const Person& p      = Person{ "Trillian" });


	float value;
	const char* cname;
	std::string name;
	Person person;
};


Test::Test(const float v, const char* c, const std::string& n, const Person& p)
:	value { v }
,	cname { c }
, name  { n }
, person{ p }
{}


}

#endif // WRAP_TEST_H_
