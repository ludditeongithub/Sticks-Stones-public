#include "entity_search.hpp"
#include "core/database.hpp"
#include "world/animal/enum.hpp"
#include "world/tile/data.hpp"
#include "world/tile/database.hpp"
#include <core/limits.hpp>
#include <core/entity.hpp>
#include <core/math.hpp>
#include <cstdint>
#include <limits>
#include <variant>
#include <world/unit/enum.hpp>
#include <world/world.hpp>

SearchGrid::SearchGrid(World& world, TileDatabase& tiles) :  world(world), tiles(tiles)
{	
	uint16_t chunk_amount = world.CHUNK_AMOUNT;
	chunkBucketArena = new Arena((chunkAmount * NATURAL_CHUNK_SEARCH_SIZE));

	activeBucketArena =
	    new Arena((chunkAmount * NATURAL_CHUNK_SEARCH_SIZE) +
		      (estimatedActiveChunkAmount(chunkAmount) * ACTIVE_CHUNK_SEARCH_SIZE));

	for (uint16_t i = 0; i < chunk_amount; i++)
	{
		chunkBuckets[i] =
		   arena_make_array<ChunkBucket*>(chunkBucketArena, NATURAL_CHUNK_SEARCH_SIZE);
		activeChunks[i] = false;
	}
    
}

inline GridInfo SearchGrid::get_nth_nearest_chunk(Coord c, uint16_t n)
{
		const uint16_t center = getChunkIndexFromTile(c);
	const int ha = c.x % CHUNK_SIZE;
	const int va = c.y % CHUNK_SIZE;
	const int dist_n = va;
	const int dist_s = CHUNK_SIZE - va;
	const int dist_w = ha;
	const int dist_e = CHUNK_SIZE - ha;

	struct Entry
	{
		uint16_t dist;
		int16_t offset;
	};

	const int row = world.LENGTH_CHUNKS;

	Entry neighbors[8] = {{static_cast<uint16_t>(dist_n), -row},
			      {static_cast<uint16_t>(dist_s), row},
			      {static_cast<uint16_t>(dist_w), -1},
			      {static_cast<uint16_t>(dist_e), 1},
			      {static_cast<uint16_t>(dist_n + dist_e), -row + 1},
			      {static_cast<uint16_t>(dist_n + dist_w), -row - 1},
			      {static_cast<uint16_t>(dist_s + dist_e), row + 1},
			      {static_cast<uint16_t>(dist_s + dist_w), row - 1}};

	const uint16_t idx = n & 7;

	std::nth_element(std::begin(neighbors), std::begin(neighbors) + idx, std::end(neighbors),
			 [](const Entry &a, const Entry &b) { return a.dist < b.dist; });

	const int target = int(center) + neighbors[idx].offset;

	GridInfo result;
	result.index =
	    (target >= 0 && target < world->CHUNK_AMOUNT) ? static_cast<uint16_t>(target) : center;
	result.distance = neighbors[idx].dist;

	return result;
}

void SearchGrid::add_active_chunk(uint16_t index)
{
	activeChunks[index] = true;
	uint16_t active_index;
	if (freeIndices.empty())
		active_index = activeCount;
	else
	{
		activeIndex = freeIndices.top();
		freeIndices.pop();
	}
	activeChunkBuckets[activeIndex] = chunkBuckets[index];
	chunkToActiveChunks[index] = activeIndex;
}

inline void SearchGrid::insert_entity(Entity type, EntitySearchData data)
{
	uint16_t gc = getChunkIndexFromTile(data.position);
	uint16_t i = getTileIndexChunkRelative(data.position);
	if (!(tiles->occupiedTiles[gc])[i])
	{
		if (activeChunks[gc])
		{			activeChunkBuckets[gc]->at(type).push_back(data);
		}
		else
		{
			chunkBuckets[gc]->at(type).push_back(data);
		}
	} // TODO: error
}

inline void SearchGrid::remove_entity(Entity type, EntitySearchData data)
{
  
}

inline bool SearchGrid::check_collision(Coord tileCoord)
{	
	return tiles->occupieds[world.getTileIndexFromCoord(tileCoord)];
}

inline EntitySearchData SearchGrid::get_nearest(Entity e, Coord c)
{
	// search per chunk, starting with nearest
	uint16_t ci = getChunkIndexFromTile(c);
	Array<SearchGrid::ChunkBucket *> &buckets = activeChunks[ci] ? activeChunkBuckets : chunkBuckets;
	uint16_t cbi = activeChunks[ci] ? chunkToActiveChunks[ci] : ci;
	auto &&es = buckets[cbi]->find(e);

	if (es != buckets[cbi]->end())
	{
		Coord nc;
		uint16_t si = SIZE_MAX;
		uint16_t ld = UINT16_MAX;
		for (uint16_t i = 0; i < es->second.size(); i++)
		{
			Coord tc = es->second[i].position;
			uint32_t td = manhattanDist(c, tc);
			if (td < ld)
			{
				ld = td;
				si = i;
			}
		}
		return es->second[si];
	}
	else
	{
		return {std::numeric_limits<uint16_t>::max(), {std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::max()}};
	}
}

inline bool check_adjacent(Entity entity, Coord coord)
{

}

inline EntitySearchData SearchGrid::get_nth_nearest(uint16_t nearest, Entity e, Coord c)
{
	uint16_t ci = getChunkIndexFromTile(c);
	Array<SearchGrid::ChunkBucket *> &buckets =
		activeChunks[ci] ? activeChunkBuckets : chunkBuckets;

	uint16_t cbi = activeChunks[ci] ? chunkToActiveChunks[ci] : ci;
	auto &&es = buckets[cbi]->find(e);

	if (es == buckets[cbi]->end())
	{
		return {
			std::numeric_limits<uint16_t>::max(),
			{
				std::numeric_limits<uint16_t>::max(),
				std::numeric_limits<uint16_t>::max()
			}
		};
	}

	const auto &list = es->second;
	const uint16_t n = list.size();

	if (nearest >= n)
	{
		return {
			std::numeric_limits<uint16_t>::max(),
			{
				std::numeric_limits<uint16_t>::max(),
				std::numeric_limits<uint16_t>::max()
			}
		};
	}

	std::vector<bool> used(n, false);

	uint16_t best_index = 0;
	uint32_t best_dist = 0;

	for (uint16_t k = 0; k <= nearest; k++)
	{
		bool found = false;

		for (uint16_t i = 0; i < n; i++)
		{
			if (used[i]) continue;

			uint32_t d = manhattanDist(c, list[i].position);

			if (!found || d < best_dist)
			{
				best_dist = d;
				best_index = i;
				found = true;
			}
		}

		used[best_index] = true;
	}

	return list[best_index];
}

EntityRenderBuffer SearchGrid::get_all_in_range(Coord origin, Coord dimensions)
{
	EntityRenderBuffer erd;
	std::vector<uint16_t> chunks_on_screen = getChunksFromArea(origin, dimensions);
	for (auto i: chunksOnScreen) {
			Array<SearchGrid::ChunkBucket *> &cb = activeChunks[i] ? activeChunkBuckets : chunkBuckets;
	uint16_t cbi = activeChunks[i] ? chunkToActiveChunks[i] : i;
	// iterate through unordered map, get all entities
	for (auto x : *cb[cbi])
	{
std::visit([&](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    std::vector<EntitySearchData>& objects = x.second;
    if constexpr (std::is_same_v<T, Plant>)
    {
	    for (size_t j = 0; j < objects.size(); j++) {
		            erd.plants[erd.plantAmount++] = {objects[j].index, objects[j].position, std::move(arg)};
	    }
    }
    else if constexpr (std::is_same_v<T, Animal>)
    {
	    for (size_t j = 0; j < objects.size(); j++) {
		            erd.animals[erd.animalAmount++] = {objects[j].index, objects[j].position, std::move(arg)};
	    }        
    }
    else if constexpr (std::is_same_v<T, Item>) {
	    for (size_t j = 0; j < objects.size(); j++) {
		            erd.items[erd.itemAmount++] = {objects[j].index, objects[j].position, std::move(arg)};
	    }
    }
    else if constexpr (std::is_same_v<T, Unit>) {
	    for (size_t j = 0; j < objects.size(); j++) {
		            erd.items[erd.itemAmount++] = {objects[j].index, objects[j].position, std::move(arg)};
	    }
    }
    else if constexpr (std::is_same_v<T, Tool>) {
	    for (size_t j = 0; j < objects.size(); j++) {
		            erd.tools[erd.toolAmount++] = {objects[j].index, objects[j].position, std::move(arg)};
	    }
    } 
}, x.first);
	}
	}
	return erd;
}


std::pair<int, int> ObjectDatabase::findNearestLiquidContainer(int x, int y)
{
	std::pair<int, int> subject = {x, y};
	std::pair<int, int> closest = findNearestObject(Container::Pot, x, y);
	if (manDist(subject, closest) <
	    manDist(findNearestObject(subject, Container::Bucket, x, y)))
		closest = findNearestObject(subject, Container::Bucket, x, y);
	if (manDist(subject, closest) <
	    manDist(findNearestObject(subject, Container::LargePot, x, y)))
		closest = findNearestObject(subject, Container::LargePot, x, y);
	if (manDist(subject, closest) <
	    manDist(findNearestObject(subject, Container::Kettle, x, y)))
		closest = findNearestObject(subject, Container::Kettle, x, y);
	if (manDist(subject, closest) < manDist(findNearestObject(subject, Container::Keg, x, y)))
		closest = findNearestObject(subject, Container::Keg, x, y);
	if (manDist(subject, closest) < manDist(findNearestObject(subject, Container::Jar, x, y)))
		closest = findNearestObject(subject, Container::Jar, x, y);
	return closest;
}
