#ifndef PYSPOT_TEST_DETAILS_H_
#define PYSPOT_TEST_DETAILS_H_

#include <cstdint>

#include "test/Common.h"

namespace pyspot
{
namespace test
{


struct PYSPOT_EXPORT Details
{
	Details( const uint32_t c ) : count{ c } {};
	uint32_t count = 0;

	bool operator==( const Details& other ) const { return count == other.count; };
};

}  // namespace test
}  // namespace pyspot

#endif  // PYSPOT_TEST_DETAILS_H_
