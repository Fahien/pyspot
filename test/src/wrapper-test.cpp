#include "wrapper-test.h"

#include <pyspot/Bindings.h>
#include <pyspot/Extension.h>

using namespace pyspot;
using namespace wrap;
using namespace std;

#if PYTHON_VERSION >= 3
# define TEST_DIR _T( "test/script/3" )
#else
# define TEST_DIR _T( "test/script/2" )
#endif

namespace test
{


Module& getModule()
{

	static Interpreter interpreter { "pyspot", PyInit_extension, TEST_DIR };
	static Module module { "wrapper" };
	return module;
}


void CanModifyMemberInt()
{
	Test test {};
	assert( test.index == 0 );
	getModule().Invoke( "modify_member_int", { Wrapper<Test>{ &test } } );
	assert( test.index == 1 && "Cannot modify member int" );
}


void CanModifyMemberFloat()
{
	Test test {};
	assert( test.value == 0.0f );
	getModule().Invoke( "modify_member_float", { Wrapper<Test>{ &test } } );
	assert( test.value == 1.0f && "Cannot modify member float" );
}


void CanModifyMemberCString()
{
	Test test {};
	assert( test.cname == "Arthur" );
	getModule().Invoke( "modify_member_cstring", { Wrapper<Test>{ &test } } );
	assert( test.cname == string{ "Dent" } && "Cannot modify member cstring" );
}


void CanModifyMemberString()
{
	Test test {};
	assert( test.name == "Ford" );
	getModule().Invoke( "modify_member_string", { Wrapper<Test>{ &test } } );
	assert( test.name == "Prefect" && "Cannot modify member string" );
}


void CanCallMethodWithArg()
{
	Test test {};
	assert( test.value == 0.0f );
	getModule().Invoke( "call_method_with_arg", { Wrapper<Test>{ &test } } );
	assert( test.value == 1.0f );
}


void CanGetMethodReturnValue()
{
	Test test {};
	assert( test.person.name == "Trillian" );
	getModule().Invoke( "get_method_return_value", { Wrapper<Test>{ &test } } );
	assert( test.person.name == "FordArthur" );
}


void CanGetCreatedObject()
{
	Wrapper<Test> wTest { getModule().Invoke( "get_created_object" ) };
	assert( wTest->index == 1 );
	assert( wTest->value == 2.0f );
	assert( wTest->cname == string{ "Deep" } );
	assert( wTest->name  == "Thought" );
	assert( wTest->person.name == "Zaphod" );
}


void CanInvokeCMethod()
{
	String ret { getModule().Invoke( "invoke_c_method" ) };
	assert( ret == "PyWrap" );
}


void CanCompareEnums()
{
	input::Input inp { input::Key::UP, input::Action::PRESS };
	getModule().Invoke( "compare_enums", { Wrapper<input::Input>{ &inp } } );

	assert( inp.key == input::Key::RIGHT && "Cannot modify enum" );
	assert( inp.action == input::Action::RELEASE && "Cannot modify enum" );
}


} // namespace test


int main()
{
	try
	{
		// Init first
		test::getModule();

		test::CanModifyMemberInt();
		test::CanModifyMemberFloat();
		test::CanModifyMemberCString();
		test::CanModifyMemberString();
		test::CanCallMethodWithArg();
		test::CanGetMethodReturnValue();
		test::CanGetCreatedObject();
		test::CanInvokeCMethod();
		test::CanCompareEnums();
	}
	catch (const Exception& ex)
	{
		wcerr << "Error: " << ex.What() << endl;
	}

	return EXIT_SUCCESS;
}
