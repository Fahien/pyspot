#include <stdlib.h>
#include "tests.h"
#include "PySpot.h"
#include "PySpotException.h"


bool test1()
{
	pyspot::PySpot pyspot{};
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
		printf("Error: %s\n", ex.what());
	}
	return false;
}