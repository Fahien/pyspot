#include "test/Product.h"
#include "test/Test.h"

namespace pyspot
{
namespace test
{
TEST_F( Python, ModifyMember )
{
	Module module{ "product-test" };

	Product apple{ "apple", 4.0f };
	module.Invoke( "discount_apple", { Wrapper<Product>{apple} } );
	ASSERT_EQ( apple.price, 3.0f );
}
}  // namespace test
}  // namespace pyspot
