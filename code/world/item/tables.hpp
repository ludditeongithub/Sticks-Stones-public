#include "enum.hpp"
#include <core/tables.hpp>

inline constexpr LookupTable<ContainerType, float> CONTAINER_WEIGHT_CAPACITIES = []
{
	LookupTable<ContainerType, float> lt{};
	using enum ContainerType;

	return lt;
}();

inline constexpr LookupTable<ContainerType, float> CONTAINER_BULK_CAPACITIES = []
{
	LookupTable<ContainerType, float> lt{};
	using enum ContainerType;

	return lt;
}();

inline constexpr RaggedLookupTable<Commodity::underlying, Action, COMMODITY_ACTIONS> COMMODITY =
    []
{
	using enum Commodity::underlying;

	RaggedLookupTable<Commodity::underlying, Action, COMMODITY_ACTIONS, > lt{};

	return lt;
}();

namespace item
{
  // @codegen:begin descriptions

  // @codegen:end descriptions

  
}  
