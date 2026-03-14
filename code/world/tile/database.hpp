#include <core/data.hpp>
#include <core/containers.hpp>
#include "enum.hpp"

class TileDatabase {
  Array<Tile> tiles;
  Array<Alt> altitudes;

  TileDatabase(WorldSpawner &ws) {
	  std::vector<float> chances = 
	  ws.generateTileTypes(tiles, altitudes);
  }

};
