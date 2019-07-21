#include "test/Product.h"
#include "test/Test.h"

namespace pyspot
{
namespace test
{

TEST_F( Python, instantiate_class )
{
	Module module{ "class-test" };

	Wrapper<Product> orange = module.call( "create_orange" );

	ASSERT_EQ( orange->name, "Orange" );
	ASSERT_EQ( orange->price, 1.0f );
}

TEST_F( Python, discount_apple )
{
	Module module{ "class-test" };

	Product          apple{ "Apple", 4.0f };
	Wrapper<Product> py_apple{ &apple };

	module.call( "discount_apple", { py_apple } );
	ASSERT_EQ( apple.price, 3.0f );
	ASSERT_TRUE( apple.discounted );

	module.call( "discount_apple", { py_apple } );
	ASSERT_EQ( apple.price, 3.0f );
}
}  // namespace test
}  // namespace pyspot
