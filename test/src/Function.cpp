#include "test/Function.hpp"
#include "test/Test.hpp"

#include "pyspot/Long.h"

namespace pyspot::test
{


TEST_CASE( "function" )
{
	get_interpreter();
	Module function_test{ "function-test" };
	Long   five{ function_test.call( "call_function" ) };
	REQUIRE( five.get_value() == 5 );
}


}  // namespace pyspot::test
