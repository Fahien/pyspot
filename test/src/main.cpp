#include "tests.h"

#include <cstdlib>


int main(void)
{
	bool success{
		testSingle() &&
		testTest()   &&
		testString() &&
		testTransform()
	};
	
	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
