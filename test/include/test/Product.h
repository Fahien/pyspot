#ifndef PYSPOT_TEST_PRODUCT_H_
#define PYSPOT_TEST_PRODUCT_H_

#include <string>

namespace pyspot
{
namespace test
{
class __attribute__( ( annotate( "pyspot" ) ) ) Product
{
  public:
	Product( const std::string& name = "Default", const float price = 1.0f ) : name{ name }, price{ price } {}

	std::string name;
	float       price;
	bool        discounted = false;
};
}  // namespace test

}  // namespace pyspot


#endif  // PYSPOT_TEST_PRODUCT_H_
