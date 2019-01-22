#include <sstream>

#include "gtest/gtest.h"

#include "pyspot/Bindings.h"
#include "pyspot/Extension.h"
#include "pyspot/Interpreter.h"
#include "pyspot/Module.h"
#include "pyspot/Tuple.h"
#include "test/Color.h"


#if PY_MAJOR_VERSION >= 3
#define TEST_DIR _T("script/3")
#else
#define TEST_DIR _T("script/2")
#endif

namespace pyspot
{
namespace test
{
class Python : public testing::Test
{
  public:
	Python();
	void SetUp() override{};
	void TearDown() override{};

  private:
	std::unique_ptr<pyspot::Interpreter> interpreter;
};

Python::Python()
    : interpreter{ new pyspot::Interpreter{ "pyspot", PyInit_pyspot,
	                                        TEST_DIR } }
{
}

TEST_F( Python, InitializeInterpreter ) { ASSERT_TRUE( Py_IsInitialized() ); }

TEST_F( Python, ImportModule )
{
	pyspot::Module pyspot{ "pyspot" };
	ASSERT_NE( pyspot.GetObject(), nullptr );
}

TEST_F( Python, CallMethod )
{
	pyspot::Module baseTest{ "base-test" };
	baseTest.Invoke( "hello" );
}

TEST_F( Python, InstantiateEnum )
{
	pyspot::Module enumTest{ "enum-test" };
	enumTest.Invoke( "create_color" );
}

TEST_F( Python, ReturnEnum )
{
	pyspot::Module         enumTest{ "enum-test" };
	pyspot::Wrapper<Color> red{ enumTest.Invoke( "create_color" ) };
	ASSERT_EQ( red.GetPayload(), Color::RED );
}

TEST_F( Python, PassEnum )
{
	pyspot::Module         enumTest{ "enum-test" };
	pyspot::Wrapper<Color> blue{ enumTest.Invoke(
		"send_color", { pyspot::Wrapper<Color>{ Color::BLUE } } ) };
	ASSERT_EQ( blue.GetPayload(), Color::BLUE );
}

TEST_F( Python, CompareEnum )
{
	pyspot::Module enumTest{ "enum-test" };
	auto           result = enumTest.Invoke( "compare_color",
                                   { pyspot::Wrapper<Color>{ Color::GREEN } } );
	ASSERT_TRUE( PyBool_Check( result.GetObject() ) );
	ASSERT_EQ( PyLong_AsLong( result.GetObject() ), 1 );
}

TEST_F( Python, ReassignEnum )
{
	pyspot::Module         enumTest{ "enum-test" };
	pyspot::Wrapper<Color> color{ Color::BLUE };
	pyspot::Wrapper<Color> result =
	    enumTest.Invoke( "change_color", { color } );
	ASSERT_EQ( result.GetPayload(), Color::RED );
	ASSERT_NE( result.GetPayload(), color.GetPayload() );
}

}  // namespace test
}  // namespace pyspot
