#include <core/data.hpp>
#include <core/containers.hpp>
#include <simulation/world_gen.hpp>
#include "enum.hpp"
#include "world/world.hpp"

class TileDatabase {
public:
  Array<TileData> tiles;
  Array<Alt> altitudes;

	TileDatabase(Arena* arena, WorldSpawner &ws, World &w) {
          std::vector<Tile> t(w.WORLD_TILE_AMOUNT);
          std::vector<float> gtc = ws.generateTileChances();
	  std::vector<Coord> gvs =  ws.generateVoronoiSites();
          ws.generateTileTypes(gtc, gvs, t, altitudes);
          ws.spawnGrassAndFirstPlants();
          tiles = arena_make_array<TileData>(arena, w.WORLD_TILE_AMOUNT);
          altitudes = arena_make_array<Alt>(arena, w.WORLD_TILE_AMOUNT);
	  
	  for (int i = 0; i < w.WORLD_TILE_AMOUNT; i++) {
            tiles[i].first() = t[i];
	    tiles[i].second() = ws.tileGrass[i];
          }
        }
};


