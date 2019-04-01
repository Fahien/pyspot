#ifndef PYSPOT_TEST_COLOR_H_
#define PYSPOT_TEST_COLOR_H_

#include "test/Common.h"

namespace pyspot
{
namespace test
{
class PYSPOT_EXPORT Coin
{
  public:
	int value;
};

enum class PYSPOT_EXPORT Color
{
	RED,
	GREEN,
	BLUE
};


}  // namespace test
}  // namespace pyspot


#endif  // PYSPOT_TEST_COLOR_H_
