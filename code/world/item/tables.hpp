#include "enum.hpp"
#include <core/tables.hpp>

inline constexpr LookupTable<ContainerType, float> containerWeightCapacities = []
{
	LookupTable<ContainerType, float> lt{};
	using enum ContainerType;

	return lt;
}();

inline constexpr LookupTable<ContainerType, float> containerBulkCapacities = []
{
	LookupTable<ContainerType, float> lt{};
	using enum ContainerType;

	return lt;
}();
