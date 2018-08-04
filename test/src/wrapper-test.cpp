#include <cstdlib>
#include <cassert>

#include <pyspot/Interpreter.h>
#include <pyspot/Module.h>
#include <pyspot/Tuple.h>
#include <pyspot/Exception.h>
#include <pyspot/Wrapper.h>

#include "pywrap/extension/Pywrap.h"
#include "pywrap/wrap/Person.h"
#include "wrap/Test.h"

using namespace pyspot;
using namespace wrap;

#if PYTHON_VERSION >= 3
# define TEST_DIR _T("test/script/3")
#else
# define TEST_DIR _T("test/script/2")
#endif


void testTest()
{
	Test test{ 2.0f };
	Wrapper<Test> wTest{ test };
	Module module{ "wrapper" };
	Object result{ module.Invoke("test_test", Tuple{ wTest }) };
	assert(test.value == 3.0f);
}


void testPerson()
{
	Person person{ "Amrik" };
	Wrapper<Person> wPerson{ person };
	Module module{ "wrapper" };
	Object result{ module.Invoke("test_person", Tuple{ wPerson }) };
	assert(person.name == "Antonio");
}


int main()
{
	Interpreter interpreter{ "pyspot", PyInit_Pywrap, TEST_DIR };

	try
	{
		testTest();
		testPerson();
	}
	catch (const Exception& ex)
	{
		fprintf(stderr, "Error %ls\n", ex.What().c_str());
	}

	return EXIT_SUCCESS;
}
