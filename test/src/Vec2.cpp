#include "test/Vec2.h"
#include "pyspot/Long.h"
#include "test/Test.h"

namespace pyspot
{
namespace test
{
TEST_F( Python, create_origin )
{
	Module module{ "vec2-test" };

	Wrapper<Vec2<int>> origin = module.call( "create_origin" );

	ASSERT_EQ( origin.GetPayload().x, 0 );
	ASSERT_EQ( origin.GetPayload().y, 0 );
}

TEST_F( Python, create_one )
{
	Module module{ "vec2-test" };

	Wrapper<Vec2<float>> one = module.call( "create_one" );

	ASSERT_EQ( one.GetPayload().x, 1.0f );
	ASSERT_EQ( one.GetPayload().y, 1.0f );
}

TEST_F( Python, modify_member )
{
	Module    module{ "vec2-test" };
	Vec2<int> origin{};

	Wrapper<Vec2<int>> py_origin{ &origin };

	module.call( "move_origin", { py_origin } );
	ASSERT_EQ( origin.x, 1.0f );
	ASSERT_EQ( origin.y, 2.0f );
}
}  // namespace test
}  // namespace pyspot
