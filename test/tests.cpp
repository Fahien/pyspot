#include <stdlib.h>
#include "tests.h"
#include "PySpot.h"


bool test1()
{
	pyspot::PySpot pyspot{};
	return true;
}


bool test2()
{
	pyspot::PySpot pyspot{};
	pyspot::PySpotModule pymodule{ pyspot.importModule("os") };
	return false;
}