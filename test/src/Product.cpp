#include "test/Product.h"
#include "test/Test.h"

namespace pyspot
{
namespace test
{
TEST_F( Python, ModifyMember )
{
	Module  module{ "product-test" };
	Product apple{ "apple", 4.0f };

	Wrapper<Product> pyApple{ &apple };

	module.Invoke( "discount_apple", { pyApple } );
	ASSERT_EQ( apple.price, 3.0f );
	ASSERT_TRUE( apple.discounted );

	module.Invoke( "discount_apple", { pyApple } );
	ASSERT_EQ( apple.price, 3.0f );
}
}  // namespace test
}  // namespace pyspot
