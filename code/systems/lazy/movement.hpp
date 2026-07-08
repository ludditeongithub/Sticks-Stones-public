#include "core/data.hpp"
#include "pathfinding.cpp"
#include "world/animal/database.hpp"
#include "world/animal/tables.hpp"
#include "world/tile/database.hpp"
#include <world/tile/tables.hpp>
#include <world/unit/defaults.hpp>
// TODO: trees and other large items block visibility

// raw inertia value
inline Frame TileDatabase::calcInertia(Frame entityBaseFrames, const Coord coord)
{
	return static_cast<Frame>(entityBaseFrames * tileFrameMultiplier[tiles[getIndex(coord)]]);
}

inline Frame TileDatabase::calcInertia(const Coord coord, bool running)
{
		Frame base;
		running ? base = BASE_RUNNING_FRAMES : base = BASE_WALKING_FRAMES;
		return static_cast<Frame>( * tileFrameMultiplier[tiledatas[getIndex(coord)].get<Tile>()]);
}

template <typename DB>
inline void move(DB& database, EntityID i, const Direction direction)
{
  Coord& coord = database.coords[i];
  coord.move(direction);  
}

template <typename DB>
inline void setNextMoveInertia(DB& database, TileDatabase& tiles, EntityID i, const Coord coord)
{
if (typeid(database) == AnimalDatabase)
  {
    Animal animal = database.animals[i];
    database.inertias[i] = tiles.calcInertia(animal::walkingFramePerTiles[animal], coord);
  }
  else
	  database.inertias[i] = tiles.calcInertia(coord);
  // TODO: speed for different units
}
