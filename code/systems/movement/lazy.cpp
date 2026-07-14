#include "core/tables.hpp"
#include "movement.hpp"
#include <world/tile/tables.hpp>
#include <world/unit/defaults.hpp>
#include "world/animal/database.hpp"
#include "world/animal/tables.hpp"
// raw inertia value
inline Frame TileDatabase::calcInertia(Frame entityBaseFrames, const Coord coord)
{
	return static_cast<Frame>(entityBaseFrames * tileFrameMultiplier[tileDatas[getIndex(coord)]]);
}

inline Frame TileDatabase::calcInertia(const Coord coord, bool running)
{
		Frame base;
		running ? base = BASE_RUNNING_FRAMES : base = BASE_WALKING_FRAMES;
		return static_cast<Frame>( * tileFrameMultiplier[tileDatas[getIndex(coord)].get<Tile>()]);
}

template <typename DB>
inline void move(DB& database, EntityID i, const Direction direction)
{
  Coord& coord = database.coords[i];
  coord.move(direction);  
}

template <typename DB>
inline void set_next_move_inertia(DB& database, TileDatabase& tiles, EntityID i, const Coord coord, bool running)
{
if (typeid(database) == AnimalDatabase)
		{
	LookupTable<Animal, Frame> frame_per_tiles_table = animal::getFramePerTilesTable(running);
		  
    Animal animal = database.animals[i];
    database.inertias[i] = tiles.calcInertia(framePerTilesTable[animal], coord);
  }
  else
		  database.inertias[i] = tiles.calcInertia(coord, running);
  // TODO: speed for different units
}

void set_next_movement_inertia() {}

else if (actions[i] == Action::Prowl ||
			 actions[i] == Action::CheckProwl)
		{ // TODO: ProwlTile
			if (rint(0, 50) < 50)
				directions[i] = getRandomAdjDirection(directions[i]);
			moveInDirection(i, false);
			// check surroundings, if target is now seen
			Object obj = currentTarget[i];
			if (actions[i] = Action::CheckProwl)
				ran = true;
			if (isItem(obj))
				itemCheck(pawn, directions[i], ran);
			else if (isPlant(obj))
				searchPlantCheck(pawn, directions[i], ran);
			else if (isScavengeable(obj))
				scavengeableCheck(pawn, directions[i], ran);
			// TODO:: Fruit
			// TODO:: animal
			else if (isTools(obj))
				toolCheck(pawn);
			inertias[i] = calcSpeed(midSpeedPawn, coords[i]);
		}
		else if (actions[i] == Action::ApproachPlant ||
			 actions[i] == Action::ApproachTile ||
			 actions[i] == Action::ApproachTool ||
			 actions[i] == Action::ApproachItem)
		{
			std::pair<Direction, bool> next = nextDirectionToTarget(i);
			direction[i] = next.first;
			if (next.second)
			{
				moveInDirection(i, false);
				inertias[i] = calcSpeed(minSpeedPawn, coords[i]);
			}
			else
			{
				if (actions[i] == Action::ApproachItem)
					takeItem(i, coords[i]);
				else if (actions[i] == Action::ApproachPlant)
					harvestPlant(i, coords[i]);
				else if (actions[i] == Action::ApproachTile)
					harvestTile(i, coords[i]);
				else if (actions[i] == Action::ApproachScavengeable)
					harvestScavengeable(i, coords[i]);
				else if (actions[i] == Action::ApproachTool)
					takeTool(i, coords[i]);
				actions[i] = Action::Idle;
				decideTask(i);
			}
		} else if (actions[i] == Action::GetTool ||
			 actions[i] == Action::GetItem)
		{
			std::pair<Direction, bool> next = nextDirectionToTarget(i);
			direction[i] = next.first;
			if (next.second)
			{
				moveInDirection(i, false);
				inertias[i] = calcSpeed(midSpeedPawn, coords[i]);
				// promised versions, while approach is non-promise
				if (actions[i] == Action::GetItem)
					takeItem(i, coords[i]);
				else
					takeTool(i, coords[i]);
				actions[i] = Action::Idle;
				findPromise.set();
			}
			else if (actions[i] == Action::Pursuit ||
				 actions[i] == Action::AnimalPursuit)
			{
				std::pair<Direction, bool> next = nextDirectionToMovingTarget(i);
				direction[i] = next.first;
				if (next.second)
					moveInDirection(i, false);
				else
				{
					if (actions[i] == Action::Pursuit)
					{
						// TODO: get new military target
						if (attack(i, currentDest[i], false, false))
							getNewTarget();
					}
					// TODO: do this
					if (actions[i] == Action::AnimalPursuit)
						if (attack(i, currentDest[i], false, true))
							dealWithGame();
				}
				inertias[i] = calcSpeed(maxSpeedPawn, coords[i]);
			}
		}
