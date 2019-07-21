#ifndef PYSPOT_TEST_PRODUCT_H_
#define PYSPOT_TEST_PRODUCT_H_

#include <string>
#include "test/Common.h"
#include "test/Details.h"

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


#endif  // PYSPOT_TEST_PRODUCT_H_
