#include <array>
#include <vector>
#include <cstdint>
#include <limits>
#include <world/unit/roles_commodities.hpp>

struct CommodityDispatcher
{
	std::array<uint8_t, ROLE_COMMODITY_JOB_AMOUNT> priorities;	

void setPriority(Role role, Commodity::underlying commodity, uint8_t priority)
{
	assert(commodity < Commodity::MAX);
	uint32_t roleIndex = static_cast<Commodity::underlying>(role);
	uint32_t roleOffset = rolesToCommodities.offsets[roleIndex];
	Commodity::underlying commodityOffset = std::numeric_limits<Commodity::underlying>::max();

	for (uint8_t i = 0; i < static_cast<uint8_t>(rolesToCommodities.size(role)); i++) {
		if (rolesToCommodities.get(role, i) == commodity) commodityOffset = i;			
	}
	priorities[roleOffset + commodityOffset] = priority;
}

static std::pair<Commodity::underlying, Commodity::underlying> getPriorityRange(Role role)
{
	//TODO: error for range issues
	return {rolesToCommodities.offsets[static_cast<uint32_t>(role)], rolesToCommodities.offsets[static_cast<uint32_t>(role) + 1]};
}	
 	
};
