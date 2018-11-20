#ifndef WRAP_TEST_H_
#define WRAP_TEST_H_

#include <string>
#include <wrap/Person.h>


namespace wrap
{

class [[pyspot::export]] Test
{
  public:
	inline Test( const int   i        = 0,
	             const float v        = 0.0f,
	             const char* c        = "Arthur",
	             const std::string& n = "Ford",
	             const Person& p      = { "Trillian" } );

	void SetValue( const float v ) { value = v; }
	std::string GetNames() const { return name + cname; }

	int index;
	float value;
	const char* cname;
	std::string name;
	Person person;
};


Test::Test( const int i, const float v, const char* c, const std::string& n, const Person& p )
:	index { i }
,	value { v }
,	cname { c }
,	name  { n }
,	person{ p }
{}


} // namespace wrap

#endif // WRAP_TEST_H_
