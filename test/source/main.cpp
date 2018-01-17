#include "tests.h"

#include <cstdlib>


int main(void)
{
	bool success{
		testSingleComponent() &&
		testTestComponent()   &&
		testStringComponent() &&
		testTransformComponent()
	};
	
	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
