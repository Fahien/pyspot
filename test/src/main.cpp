#include "tests.h"

#include <cstdlib>


int main(void)
{
	bool success{
		testHello()  &&
		testSingle() &&
		testTest()   &&
		testString() &&
		testTransform()
	};
	
	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
