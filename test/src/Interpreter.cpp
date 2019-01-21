#include "test/Test.h"

#include <gtest/gtest.h>

#include "pyspot/Interpreter.h"


namespace pyspot
{
namespace test
{


TEST( Interpreter, Instantiate )
{
	Interpreter interpreter {};
	ASSERT_TRUE( interpreter.IsInitialized() );
}


} // namespace test
} // namespace pyspot
