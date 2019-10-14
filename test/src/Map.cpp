#include "test/Week.hpp"
#include "test/Test.hpp"

namespace pyspot::test
{


TEST_CASE( "map" )
{
	get_interpreter();

	Module module{ "map-test" };

	SECTION( "instantiate" )
	{
		Wrapper<Week> week = module.call( "create_week" );
		REQUIRE( week->days[1] == "monday" );
	}

	SECTION( "modify" )
	{
		Week week {};
		Wrapper<Week> py_week { &week };

		module.call( "modify_monday", { py_week } );
		REQUIRE( week.days[1] == "tuesday" );
	}
}

}  // namespace pyspot::test
