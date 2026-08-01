#include <world/action/enum.hpp>
#include <world/unit/roles_and_actions.hpp>
#include <world/unit/database.hpp>
#include <world/buildable/defaults.hpp>
#include <systems/search/search.hpp>
#include "core/entity.hpp"
#include "inventory.hpp"
#include "world/buildable/enum.hpp"

inline bool check_action_requirement_status(ActionRequirement action_reqs, Inventory& inventory, EntityID unit_index, Coord coord)
{
	bool found = false;
        if (auto *entity = std::get_if<Item>(&action_reqs.requirement)) {
	  uint16_t amount_found = remove_item(inventory, *entity, 1, true);
          found = amount_found >= action_reqs.amount;
	}
	else //buildable
{
// TODO: certain mode can be on, which allows pawns to move movable
// buildables next to each other to accompish their job
Buildable buildable = std::get<Buildable>(action_reqs.requirement);
// TODO: different buildables have a different valid distance for working
EntitySearchData esd = g_search->get_nearest(buildable, coord);
 found = (esd.position.has_value() && manhattan_dist(esd.position, coord) < buildable::MAX_WORK_DIST);
}
  return found;
}

inline ActionRequirementData get_action_requirement_search_data(const ActionRequirement& action_reqs, Coord coord)
{
	ActionRequirementData ard;
        EntitySearchData esd;
if (auto *entity = std::get_if<Item>(&action_reqs.requirement))
			  {
				  esd = g_search->get_nearest(*entity, coord);
                                  if (esd.position.has_value) ard.type = TargetType::Item;                                        
                          }
				else
				{
					Buildable buildable = std::get<Buildable>(action_reqs.requirement);
					esd = g_search->get_nearest(buildable, coord);
					if (esd.position.has_value) ard.type = TargetType::Buildable;
				}

				ard.esd = esd;
                                return ard;
}

inline bool set_requirement_as_unit_target(unit::Database& database, EntityID index, ActionRequirementData& ard)
{
	if (ard.esd.position.has_value)
	{
          database.target_type(index) = ard.type;
          database.target(index) = ard.esd.index;
          return true;
        } else return false;
}

NecessaryActionRequirementsBuffer check_necessary_action_requirements(unit::Database& database, Action action, Inventory& inventory, EntityID unit_index, Coord coord)
{
	NecessaryActionRequirementsBuffer buffer;

	// get inputs from recipe		
                int action_reqs_amount= action_to_tools.get(action).size();                
		int found_tools = 0;
		int currently_searched = 0;
                std::vector<size_t> found_tools_replaceables(action_reqs_amount);

			for (int i = 0; i < action_reqs_amount; i++)
			{
			  ActionRequirement action_req = action_to_tools.get(action)[i];
			  bool requirement_is_tool = std::holds_alternative<Tool>(action_req);
                          size_t requirement_slot = action_req.index;
			// skip if replaceable equivalent has already been found
                          for (int j = 0; j < currently_searched; j++) {
				if (found_tools_replaceables[j] == requirement_slot) continue;                        
			// skip if tool is optional TODO: have bonus written to buffer if found
			if (requirement_slot < 0) continue;
                        
                        bool found = check_action_requirement_status(action_req, inventory, unit_index, coord);

			if (found)
			{
                          found_tools_replaceables[found_tools++] = requirement_slot;
                          continue;
			}
			else
			{
                          ActionRequirementData ard = get_action_requirement_search_data(action_req, coord);
			  bool valid_target =
			      set_requirement_as_unit_target(database, unit_index, ard);

			  if (valid_target)
			  {		   	  
			    requirement_is_tool ? buffer.tools_state = ToolsFoundState::Finding : buffer.buildables_state = BuildablesFoundState::Finding;
			  }
                        } 
		
			if (!found) {
			    EntitySearchData data = search.get_nearest(tool, coord.first, coord.second);
			    if (man_dist(coord, new_dest) > MID_GATHER_RANGE) {
				    buffer.tools_state = ToolsFoundState::Finding;
				    buffer.destination.value() = NewDest;				    // buffer.missing_tool_type.value() = tool;
				    return buffer;
                            }
			}
			else
			{
			        requirement_is_tool ? buffer.tools_state = ToolsFoundState::CannotFind : buffer.buildables_state = BuildablesFoundState::CannotFind;
				return buffer;
                        }

			// TODO:: "search home function", which checks if a pawn's home/workplace
			// contains the necessary tools, giving user warning if not
                          }
			    currently_searched++;
		}
		return buffer;
	}


