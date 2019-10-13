#include "test/Product.hpp"
#include "test/Test.hpp"

namespace pyspot::test
{


TEST_CASE( "class" )
{
	get_interpreter();

	SECTION( "instantiate_class" )
	{
		Module module{ "class-test" };

		Wrapper<Product> orange = module.call( "create_orange" );

		REQUIRE( orange->name == "Orange" );
		REQUIRE( orange->price == 1.0f );
	}

	SECTION( "discount_apple" )
	{
		Module module{ "class-test" };

		Product          apple{ "Apple", 4.0f };
		Wrapper<Product> py_apple{ &apple };

		module.call( "discount_apple", { py_apple } );
		REQUIRE( apple.price == 3.0f );
		REQUIRE( apple.discounted );

		module.call( "discount_apple", { py_apple } );
		REQUIRE( apple.price == 3.0f );
	}

}

}  // namespace pyspot::test
