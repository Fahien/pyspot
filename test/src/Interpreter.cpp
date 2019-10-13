#include "test/Test.hpp"

namespace pyspot::test
{


TEST_CASE( "interpreter" )
{
	auto& interpreter = get_interpreter();
	REQUIRE( interpreter.IsInitialized() );
}


}  // namespace pyspot::test
