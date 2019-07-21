#include "test/Color.h"
#include "test/Test.h"


namespace pyspot
{
namespace test
{
TEST_F( Python, ImportModule )
{
	Module pyspot{ "pyspot" };
	ASSERT_NE( pyspot.GetObject(), nullptr );
}


TEST_F( Python, CallMethod )
{
	Module baseTest{ "base-test" };
	baseTest.call( "hello" );
}


TEST_F( Python, InstantiateEnum )
{
	Module enumTest{ "enum-test" };
	enumTest.call( "create_color" );
}


TEST_F( Python, ReturnEnum )
{
	Module         enumTest{ "enum-test" };
	Wrapper<Color> red{ enumTest.call( "create_color" ) };
	ASSERT_EQ( red.GetPayload(), Color::RED );
}


TEST_F( Python, PassEnum )
{
	Module         enumTest{ "enum-test" };
	Wrapper<Color> blue{ enumTest.call( "send_color", { Wrapper<Color>{ Color::BLUE } } ) };
	ASSERT_EQ( blue.GetPayload(), Color::BLUE );
}


TEST_F( Python, CompareEnum )
{
	Module enumTest{ "enum-test" };
	auto   result = enumTest.call( "compare_color", { Wrapper<Color>{ Color::GREEN } } );
	ASSERT_TRUE( PyBool_Check( result.GetObject() ) );
	ASSERT_EQ( PyLong_AsLong( result.GetObject() ), 1 );
}


TEST_F( Python, ReassignEnum )
{
	Module         enumTest{ "enum-test" };
	Wrapper<Color> color{ Color::BLUE };
	Wrapper<Color> result = enumTest.call( "change_color", { color } );
	ASSERT_EQ( result.GetPayload(), Color::RED );
	ASSERT_NE( result.GetPayload(), color.GetPayload() );
}


}  // namespace test
}  // namespace pyspot
