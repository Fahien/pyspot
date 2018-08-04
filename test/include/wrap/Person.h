#ifndef WRAP_PERSON_H_
#define WRAP_PERSON_H_

namespace wrap
{

class Person
{
  public:
	Person(const std::string& n) : name{ n } {}

	std::string name;
};


}

#endif // WRAP_PERSON_H_
