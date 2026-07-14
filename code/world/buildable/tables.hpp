#pragma once

#include <core/tables.hpp>
#include <core/data.hpp>
#include "enum.hpp"

namespace buildable
{    

inline constexpr LookupTable<Buildable,Health> MAX_HEALTHS = [] {
		LookupTable<Buildable,Health> lt{};
		using enum Buildable;
		
		return lt;
}();

}
