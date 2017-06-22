#include <iostream>
#include "tests.h"

int main()
{
	return !(test1() && test2()); // false means test passed
}