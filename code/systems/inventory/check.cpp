#include <world/action/enum.hpp>
#include <world/unit/roles_and_actions.hpp>
#include <world/unit/database.hpp>
#include <systems/search/entity_search.hpp>
#include "core/entity.hpp"
#include "inventory.hpp"
#include "world/buildable/enum.hpp"

inline bool check_action_requirement_in_inventory(ActionRequirement& actionReqs, Inventory& inventory, EntityID unitIndex, Coord coord)
{
  bool found = false;
  if (auto* entity = std::get_if<Item>(&actionReqs.requirement)) found = removeItem(inventory, unitIndex, *entity, true); // TODO: investigate why not checkItem?
else //buildable
{
// TODO: certain mode can be on, which allows pawns to move movable
// buildables next to each other to accompish their job
Buildable buildable = std::get<Buildable>(actionReqs.requirement);
// TODO: different buildables have a different valid distance for working
EntitySearchData esd = g_Search->getNearest(buildable, coord);
 if (esd.position.has_value() && manhattanDist(esd.position, coord) < MAX_BUILDABLE_WORK_DIST) 
}
  return found;
}

inline void set_action_requirement_target()
{

}

NecessaryActionRequirementsBuffer check_necessary_action_requirements(UnitDatabase& database, Action action, Inventory& inventory, EntityID unitIndex, Coord coord)
{
	NecessaryActionRequirementsBuffer buffer;

	// get inputs from recipe		
                int action_reqs_amount= actionToTools.get(action).size();                
		int found_tools = 0;
		int currently_searched = 0;
                std::vector<size_t> foundToolsReplaceables(actionReqsAmount);

			for (int i = 0; i < action_reqs_amount; i++)
			{
                          const ActionRequirement action_reqs  = actionToTools.get(action)[i];
                          size_t requirement_slot = actionReqs.index;
			// skip if replaceable equivalent has already been found
			for (int j = 0; j < currently_searched; j++)
				if (foundToolsReplaceables[j] == requirementSlot) continue;                        
			// skip if tool is optional TODO: have bonus written to buffer if found
			if (requirement_slot < 0) continue;
                        
                        bool found = checkActionRequirementInInventory(actionReqs, Inventory& inventory, EntityID unitIndex, Coord coord);
                        
			if (!found)
			{
                          EntitySearchData esd;
			  if (auto *entity = std::get_if<Item>(&actionReqs.requirement))
			  {
				  esd = g_Search->getNearest(*entity, coord);
                                  if (esd.position.has_value)
					{
						database.targets(unitIndex) = esd.index;						database.target_types(unitIndex) = TargetType::Item;
                                        }
                          }
				else
				{
					Buildable buildable =
					    std::get<Buildable>(actionReqs.requirement);
					esd = g_Search->getNearest(buildable, coord);
					if (esd.position.has_value)
					{
						database.targets(unitIndex) = esd.index;
                                                database.target_types(unitIndex) = TargetType::Buildable;
                                        }
                        }
			if (esd.position.has_value) buffer.toolsState = ToolsFoundState::Finding;
                        }
							  // TODO: add to list
			
				if (found) {
				    foundToolsReplaceables[foundTools++] = requirementSlot;
				    found = true;
				    break;
				    } 

			    if (!found) {
			    data = search.getNearest(tool, coord.first, coord.second);
			    if (manDist(coord, newDest) > MID_GATHER_RANGE) {
				    buffer.state = ToolsState::Finding;
				    buffer.destination.value() = NewDest;				    // buffer.missingToolType.value() = tool;
				    return buffer;
			}
			else
			{
				buffer.state = ToolsState::CannotFind;
				return buffer;
			}
			    }				
				
			// TODO:: "search home function", which checks if a pawn's home/workplace
			// contains the necessary tools, giving user warning if not
			    currently_searched++;
		}
		buffer.state = ToolsState::FoundAll;
		return buffer;
	}
