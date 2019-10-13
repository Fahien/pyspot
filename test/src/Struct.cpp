#include <pyspot/Bool.h>

#include "test/Details.hpp"
#include "test/Test.hpp"


namespace pyspot::test
{

TEST_CASE( "struct" )
{
	get_interpreter();

	SECTION( "instantiate" )
	{
		Module struct_test{ "struct-test" };
		struct_test.call( "create_details" );
	}

	SECTION( "return" )
	{
		Module           struct_test{ "struct-test" };
		Wrapper<Details> one = struct_test.call( "create_details" );
		REQUIRE( one->count == 1 );
		REQUIRE( one->thing.value == 1 );
	}

	SECTION( "pass" )
	{
		Module           struct_test{ "struct-test" };
		Wrapper<Details> two = struct_test.call( "send_details", { Wrapper<Details>{ Details{ 2 } } } );
		REQUIRE( two->count == 2 );
	}

	SECTION( "compare" )
	{
		Module struct_test{ "struct-test" };
		Bool   result = struct_test.call( "compare_details", { Wrapper<Details>{ Details{ 3 } } } );
		REQUIRE( result );
		REQUIRE( PyLong_AsLong( result.GetObject() ) == 1 );
	}

	SECTION( "reassign" )
	{
		Module           struct_test{ "struct-test" };
		Wrapper<Details> details{ Details{ 5 } };
		Wrapper<Details> result = struct_test.call( "change_details", { details } );
		REQUIRE( result->count == 6 );
		REQUIRE( result->count != details->count );
	}
}

}  // namespace pyspot::test
