#include "test/Color.hpp"
#include "test/Test.hpp"


namespace pyspot::test
{
TEST_CASE( "enum" )
{
	get_interpreter();

	SECTION( "ImportModule" )
	{
		Module pyspot{ "pyspot" };
		REQUIRE( pyspot.GetObject() != nullptr );
	}

	SECTION( "CallMethod" )
	{
		Module baseTest{ "base-test" };
		baseTest.call( "hello" );
	}

	SECTION( "InstantiateEnum" )
	{
		Module enumTest{ "enum-test" };
		enumTest.call( "create_color" );
	}

	SECTION( "ReturnEnum" )
	{
		Module         enumTest{ "enum-test" };
		Wrapper<Color> red{ enumTest.call( "create_color" ) };
		REQUIRE( red.GetPayload() == Color::RED );
	}

	SECTION( "PassEnum" )
	{
		Module         enumTest{ "enum-test" };
		Wrapper<Color> blue{ enumTest.call( "send_color", { Wrapper<Color>{ Color::BLUE } } ) };
		REQUIRE( blue.GetPayload() == Color::BLUE );
	}

	SECTION( "CompareEnum" )
	{
		Module enumTest{ "enum-test" };
		auto   result = enumTest.call( "compare_color", { Wrapper<Color>{ Color::GREEN } } );
		REQUIRE( PyBool_Check( result.GetObject() ) );
		REQUIRE( PyLong_AsLong( result.GetObject() ) == 1 );
	}

	SECTION( "ReassignEnum" )
	{
		Module         enumTest{ "enum-test" };
		Wrapper<Color> color{ Color::BLUE };
		Wrapper<Color> result = enumTest.call( "change_color", { color } );
		REQUIRE( result.GetPayload() == Color::RED );
		REQUIRE( result.GetPayload() != color.GetPayload() );
	}
}

}  // namespace pyspot::test
