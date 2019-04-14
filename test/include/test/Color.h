#ifndef PYSPOT_TEST_COLOR_H_
#define PYSPOT_TEST_COLOR_H_

#include "test/Common.h"

namespace pyspot::test
{


struct PYSPOT_EXPORT Coin
{
	int value;
};


enum class PYSPOT_EXPORT Color
{
	RED,
	GREEN,
	BLUE
};


}  // namespace pyspot::test

#endif  // PYSPOT_TEST_COLOR_H_
