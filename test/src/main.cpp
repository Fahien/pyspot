#include "tests.h"

#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;


int main(void)
{
	bool success = false;
	try
	{
		success =
			testHello()  &&
			testSingle() &&
			testTest()   &&
			testString() &&
			testTransform() &&
			testInput() &&
			testMap() &&
			testDictionary() &&
			testBuildCustomPythonObject()
		;
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}

	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
