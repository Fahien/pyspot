#pragma once

#include "test/Common.hpp"

namespace pyspot::test
{


template <typename T>
struct PYSPOT_EXPORT Vec2
{
	T x;
	T y;

	void add( T xx, T yy )
	{
		x += xx;
		y += yy;
	}
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;


}  // namespace pyspot::test
