#include <optional>
#include <world/item/database.hpp>
#include <world/unit/database.hpp>
#include <world/item/recipes.hpp>
#include <world/unit/roles_and_actions.hpp>

// =========================
// CHECKS
// =========================

// TODO: finding mechanisms for bonus reqs
enum class ToolsFoundState
	{
		FoundAll = 0,
		Finding = 1,
		CannotFind = 2
	};

enum class BuildablesFoundState
{
	FoundAll,
	Finding,
        CannotFind
};

struct NecessaryActionRequirementsBuffer
{
        ToolsFoundState toolsState;
        BuildablesFoundState buildablesState;
  std::array<std::optional<Coord>, ACTION_MAX_REQUIREMENTS> destinations;
  std::array<std::optional<uint32_t>, ACTION_MAX_REQUIREMENTS> missingRequirementIndices;
};


