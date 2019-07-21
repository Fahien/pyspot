#include "test/Function.h"
#include "test/Test.h"

#include "pyspot/Long.h"

namespace pyspot
{
namespace test
{
TEST_F( Python, CallFunctionFromPython )
{
	Module function_test{ "function-test" };
	Long   five{ function_test.call( "call_function" ) };
	ASSERT_EQ( five.get_value(), 5 );
}
}  // namespace test
}  // namespace pyspot
