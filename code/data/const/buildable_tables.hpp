#pragma once
#include <data/types/buildable.hpp>
#include <core/tables.hpp>
#include <data/types/aliases.hpp>
#include <core/info.hpp>

namespace buildable
{
inline constexpr LookupTable<Buildable, Health> MAX_HEALTHS = []
{
	LookupTable<Buildable, Health> lt{};
	using enum Buildable;

	return lt;
}();

// @codegen:begin description
//
// @codegen:end description


}
