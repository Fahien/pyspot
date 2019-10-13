#pragma once

#include <string>
#include "test/Common.hpp"
#include "test/Details.hpp"

namespace pyspot::test
{

class PYSPOT_EXPORT Product
{
  public:
	Product( const std::string& name, const float price ) : name{ name }, price{ price } {}

	std::string name;
	float       price;
	bool        discounted = false;

	Details details = {1};
};

}  // namespace pyspot::test
