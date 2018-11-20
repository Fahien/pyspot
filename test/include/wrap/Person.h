#ifndef WRAP_PERSON_H_
#define WRAP_PERSON_H_

#include <string>


namespace wrap
{


class [[pyspot::export]] Person
{
  public:
	Person( const std::string& n = "" ) : name { n } {}

	const std::string& GetName() const { return name; }

	std::string name;
};


} // namespace wrap

#endif // WRAP_PERSON_H_
