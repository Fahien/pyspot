#include <pyspot/Bool.h>

#include "test/Details.h"
#include "test/Test.h"


namespace pyspot
{
namespace test
{


TEST_F( Python, instantiate_struct )
{
	Module struct_test{ "struct-test" };
	struct_test.call( "create_details" );
}


TEST_F( Python, return_struct )
{
	Module           struct_test{ "struct-test" };
	Wrapper<Details> one = struct_test.call( "create_details" );
	ASSERT_EQ( one->count, 1 );
}


TEST_F( Python, pass_struct )
{
	Module           struct_test{ "struct-test" };
	Wrapper<Details> two = struct_test.call( "send_details", { Wrapper<Details>{ Details{ 2 } } } );
	ASSERT_EQ( two->count, 2 );
}


TEST_F( Python, compare_struct )
{
	Module struct_test{ "struct-test" };
	Bool   result = struct_test.call( "compare_details", { Wrapper<Details>{ Details{ 3 } } } );
	ASSERT_TRUE( result );
	ASSERT_EQ( PyLong_AsLong( result.GetObject() ), 1 );
}


TEST_F( Python, reassign_struct )
{
	Module           struct_test{ "struct-test" };
	Wrapper<Details> details{ Details{ 5 } };
	Wrapper<Details> result = struct_test.call( "change_details", { details } );
	ASSERT_EQ( result->count, 6 );
	ASSERT_NE( result->count, details->count );
}


}  // namespace test
}  // namespace pyspot
