#include "test/Week.hpp"
#include "test/Test.hpp"

namespace pyspot::test
{


TEST_CASE( "array" )
{
	get_interpreter();

	Module module{ "array-test" };

	SECTION( "instantiate" )
	{
		Wrapper<Week> week = module.call( "create_week" );

		REQUIRE( week->day_numbers[0] == 1 );
	}

	SECTION( "modify" )
	{
		Week week {};
		Wrapper<Week> py_week{ &week };

		module.call( "increase_monday", { py_week } );
		REQUIRE( week.day_numbers[0] == 2 );
	}

}

}  // namespace pyspot::test
