#pragma once

#include <map>
#include <string>

#include "test/Common.hpp"
namespace pyspot::test
{


struct PYSPOT_EXPORT Week
{
	int day_numbers[7] = { 1, 2, 3, 4, 5, 6, 7 };

	std::map<int, std::string> days = {
		{ 1, "monday" },
		{ 2, "tuesday" },
		{ 3, "wednesday" },
		{ 4, "thursday" },
		{ 5, "friday" },
		{ 6, "saturday" },
		{ 7, "sunday" }
	};
};


} // namespace pyspot::test
