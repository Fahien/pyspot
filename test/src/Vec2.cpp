#include "pyspot/Long.h"

#include "test/Vec2.hpp"
#include "test/Test.hpp"

namespace pyspot::test
{

TEST_CASE( "vec2" )
{
	get_interpreter();

	SECTION( "create_origin" )
	{
		Module module{ "vec2-test" };

		Wrapper<Vec2<int>> origin = module.call( "create_origin" );

		REQUIRE( origin.GetPayload().x == 0 );
		REQUIRE( origin.GetPayload().y == 0 );
	}

	SECTION( "create_one" )
	{
		Module module{ "vec2-test" };

		Wrapper<Vec2<float>> one = module.call( "create_one" );

		REQUIRE( one.GetPayload().x == 1.0f );
		REQUIRE( one.GetPayload().y == 1.0f );
	}

	SECTION( "modify_member" )
	{
		Module    module{ "vec2-test" };
		Vec2<int> origin{};

		Wrapper<Vec2<int>> py_origin{ &origin };

		module.call( "move_origin", { py_origin } );
		REQUIRE( origin.x == 1.0f );
		REQUIRE( origin.y == 2.0f );
	}
}

}  // namespace pyspot::test
