#include "database.hpp"


	TileDatabase::TileDatabase(Arena *arena, TileSpawnBuffer &tsb, World *world)
	{
		this->world = world;
		tiles = arena_make_array<TileData>(arena, world->WORLD_TILE_AMOUNT);
		altitudes = arena_make_array<Alt>(arena, world->WORLD_TILE_AMOUNT);
		occupieds = std::vector<bool>(world->WORLD_TILE_AMOUNT);

		for (uint32_t i = 0; i < world->WORLD_TILE_AMOUNT; i++)
		{
			TileData &td = tiles[i];
			tiles[i].first() = tsb.tiles[i];
			tiles[i].second() = tsb.grass[i];
			altitudes[i] = tsb.altitudes[i];
		}
	}


	Coord TileDatabase::getNearestEmptyTile(Coord coord)
	{
		int index = world->getTileIndexFromCoord(coord);
		SCoord vectors[4] = {{0, 1}, {1, 0}, {-1, 0}, {1, 0}};

		bool found = false;
		std::queue<Coord> queue;
		queue.push(coord);
		while (!found)
		{
			Coord target = queue.front();
			queue.pop();
			for (size_t i = 0; i < 4; i++) {
				Coord candidate = {
				    std::min(world->WORLD_TILE_LENGTH, target.x + vectors[i].x),
				    std::min(world->WORLD_TILE_LENGTH, target.y + vectors[i].y)};
				if (occupieds[getChunkIndexFromTile(candidate)])
					return candidate;
				else queue.push(candidate);
			}
		}
	}		
