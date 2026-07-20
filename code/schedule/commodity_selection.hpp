#include <array>
#include <vector>
#include <cstdint>
#include <limits>
#include <world/unit/roles_commodities.hpp>

struct CommodityDispatcher
{
	std::array<uint8_t, ROLE_COMMODITY_JOB_AMOUNT> priorities;	

void set_priority(Role role, Commodity::underlying commodity, uint8_t priority)
{
	assert(commodity < Commodity::MAX);
	uint32_t role_index = static_cast<Commodity::underlying>(role);
	uint32_t role_offset = roles_to_commodities.offsets[role_index];
	Commodity::underlying commodity_offset = std::numeric_limits<Commodity::underlying>::max();

	for (uint8_t i = 0; i < static_cast<uint8_t>(roles_to_commodities.size(role)); i++) {
		if (roles_to_commodities.get(role, i) == commodity) commodity_offset = i;			
	}
	priorities[role_offset + commodity_offset] = priority;
}

static std::pair<Commodity::underlying, Commodity::underlying> get_priority_range(Role role)
{
	//TODO: error for range issues
	return {roles_to_commodities.offsets[static_cast<uint32_t>(role)], roles_to_commodities.offsets[static_cast<uint32_t>(role) + 1]};
}	
 	
};
