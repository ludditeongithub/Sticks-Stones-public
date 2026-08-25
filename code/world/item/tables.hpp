#include "enum.hpp"
#include <core/tables.hpp>

inline constexpr LookupTable<ContainerType, float> container_weight_capacities = []
{
	LookupTable<ContainerType, float> lt{};
	using enum ContainerType;

	return lt;
}();

inline constexpr LookupTable<ContainerType, float> container_bulk_capacities = []
{
	LookupTable<ContainerType, float> lt{};
	using enum ContainerType;

	return lt;
}();

inline constexpr RaggedLookupTable<Commodity::underlying, Action, COMMODITY_ACTIONS> commodity =
    []
{
	using enum Commodity::underlying;

	RaggedLookupTable<Commodity::underlying, Action, COMMODITY_ACTIONS, > lt{};

	return lt;
}();

namespace item
{
  inline constexpr LookupTable<Item,const char*> descriptions = [] {
    LookupTable<Item,const char*> lt{};
    using enum Item;
    
    return lt;
  }();
}  
