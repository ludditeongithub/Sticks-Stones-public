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

inline constexpr RaggedLookupTable<Commodity::underlying, Action, COMMODITY_ACTIONS>
commodity = []
	{
		using enum Commodity::underlying;

		RaggedLookupTable<Commodity::underlying, Action, COMMODITY_ACTIONS, > lt{};

		return lt;
	}
