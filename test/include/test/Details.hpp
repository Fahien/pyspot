#pragma once

#include <cstdint>

#include "test/Common.hpp"

namespace pyspot::test
{


struct Details
{
	Details( const uint32_t c ) : count{ c } {};
	uint32_t count = 0;

	bool operator==( const Details& other ) const { return count == other.count; };
};


}  // namespace pyspot::test

