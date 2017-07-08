#include "tests.h"
#include "PySpot.h"
#include "PySpotException.h"
#include "module/pytestmodule.h"


bool test1()
{
	pyspot::PySpot pyspot{};
	pyspot::PySpotModule pymodule{ pyspot.importModule("hello") };
	try
	{
		pyspot::PySpotObject result{ pymodule.callFunction("hello") };
		printf("Test 1 result = %ls\n", result.toString().c_str());
	}
	catch (const pyspot::PySpotException & ex)
	{
		printf("Error: %s\n", ex.what());
	}
	return true;
}


bool test2()
{
	pyspot::PySpot pyspot{};
	pyspot::PySpotModule pymodule{ pyspot.importModule("hello") };
	try
	{
		pyspot::PySpotObject result{ pymodule.callFunction("helo") };
		printf("Test 2 result = %ls\n", result.toString().c_str());
	}
	catch (const pyspot::PySpotException & ex)
	{
		printf("Error correctly captured: %s\n", ex.what());
	}
	return true;
}


bool test3()
{
	PyImport_AppendInittab("pytest", PyInit_pytest);
	pyspot::PySpot pyspot{};
	pyspot::PySpotModule pymodule{ pyspot.importModule("script") };
	printf("Test3: test_function\n");
	pymodule.callFunction("test_function");
	
	return false;
}
