#include <optional>
#include <world/item/entity.hpp>
#include <world/unit/entity.hpp>

enum class ToolsState
	{
		FoundAll = 0,
		Finding = 1,
		CannotFind = 2
	};

struct NecessaryToolsBuffer
{	
	ToolsState state;
	std::optional<Coord> destination;
	std::optional<uint32_t> target;
};


