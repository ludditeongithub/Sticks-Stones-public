#include "simulation/game.hpp"
#include "world/unit/database.hpp"
#include <systems/action/action.hpp>
#include <systems/movement/movement.hpp>
#include <systems/movement/pathfinding.hpp>

void handle_actions_and_movement_loop()
{
	// For each frame {
	// mark which entities need a new action (Action = Assign), (note: when
	// Action = Assign, ActState is irrelevant), for these entities do assign_tasks. this
	// ensures no entities at start of loop are 'assign'
	assign_unassigned_entities();

        // mark which entities have 0 inertia

  // for each entity with 0 inertia (depends on ActState) {
  // for entities that need a new path:
  // run astar on them.
  // switch them back to walking/running depending on the action
	PathsBuffer paths = get_new_paths<UnitDatabase>(g_game->unit_database);
        

// for entities that are walking/running {
// mark which entities need to check if an object is nearby (prowling) or are approaching an object,
// or simply moving a tile. send to MovingStateDispatchBuffer.
  MovingStateDispatchBuffer moving_state_dispatch_buffer = mark_entities_moving_state();
 
// for entities that are 'prowling' for an object {
// check if object is within range
// if in range, change to approaching
// otherwise keep prowling 
// }
  handle_prowlers(moving_state_dispatch_buffer.check_near_targets);
  // for entities that are approaching a prowled-for object {
  // ensure object is still 'approachable'  (may be too fast, or taken by another entity)
  handle_approachers(moving_state_dispatch_buffer.approachs);
  // move towards object (path for this is derived in normal way)
  // if mandist = 1 then interact with object according to action (change ActState to Act)
  handle_movers(moving_state_dispatch_buffer.moving_tiles); 
// }
// for entities that are normally moving {
// move at appropriate speed
// changed to new path if reached end of calculated path
// change to act if reached destination (target) }
// }

// for entities that are acting:
// if resource:
// handle_resource_action
// if product:
// handle_product_action
// if support:
// handle_support_action
// for each entity }

// } for each frame

}
