#pragma once

#include <cstdint>

#include "test/Common.hpp"

namespace pyspot::test
{


struct Details
{
	struct Thing
	{
		uint32_t value = 0;
	};

	Details( const uint32_t c ) : count{ c } {};

	uint32_t count = 0;
	Thing thing;

	bool operator==( const Details& other ) const { return count == other.count; };
};


}  // namespace pyspot::test

