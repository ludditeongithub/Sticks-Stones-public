#pragma once

#include <core/tables.hpp>
#include <core/data.hpp>
#include "enum.hpp"

namespace buildable
{    

inline constexpr LookupTable<Buildable,Health> maxHealths = [] {
		LookupTable<Buildable,Health> lt{};
		using enum Buildable;
		
		return lt;
}();

}
