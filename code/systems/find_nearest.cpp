#include "find_nearest.hpp"
#include "core/entity.hpp"
#include "world/animal/enum.hpp"
#include "world/tile/data.hpp"
#include "world/tile/database.hpp"
#include <core/limits.hpp>
#include <core/math.hpp>
#include <cstdint>
#include <limits>
#include <variant>
#include <world/unit/enum.hpp>
#include <world/world.hpp>

SearchGrid::SearchGrid(World& world, TileDatabase& tiles) :  world(world), tiles(tiles)
{	
	uint16_t chunkAmount = world.CHUNK_AMOUNT;
	chunkBucketArena = new Arena((chunkAmount * NATURAL_CHUNK_SEARCH_SIZE));

	activeBucketArena =
	    new Arena((chunkAmount * NATURAL_CHUNK_SEARCH_SIZE) +
		      (estimatedActiveChunkAmount(chunkAmount) * ACTIVE_CHUNK_SEARCH_SIZE));

	for (uint16_t i = 0; i < chunkAmount; i++)
	{
		chunkBuckets[i] =
		   arena_make_array<ChunkBucket *>(chunkBucketArena, NATURAL_CHUNK_SEARCH_SIZE);
		activeChunks[i] = false;
	}
    
}

inline GridInfo SearchGrid::getNthNearestChunk(Coord c, uint16_t n)
{
		const uint16_t center = getChunkIndexFromTile(c);
	const int ha = c.x % CHUNK_SIZE;
	const int va = c.y % CHUNK_SIZE;
	const int distN = va;
	const int distS = CHUNK_SIZE - va;
	const int distW = ha;
	const int distE = CHUNK_SIZE - ha;

	struct Entry
	{
		uint16_t dist;
		int16_t offset;
	};

	const int row = world.LENGTH_CHUNKS;

	Entry neighbors[8] = {{static_cast<uint16_t>(distN), -row},
			      {static_cast<uint16_t>(distS), row},
			      {static_cast<uint16_t>(distW), -1},
			      {static_cast<uint16_t>(distE), 1},
			      {static_cast<uint16_t>(distN + distE), -row + 1},
			      {static_cast<uint16_t>(distN + distW), -row - 1},
			      {static_cast<uint16_t>(distS + distE), row + 1},
			      {static_cast<uint16_t>(distS + distW), row - 1}};

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

void SearchGrid::addActiveChunk(uint16_t index)
{
	activeChunks[index] = true;
	uint16_t activeIndex;
	if (freeIndices.empty())
		activeIndex = activeCount;
	else
	{
		activeIndex = freeIndices.top();
		freeIndices.pop();
	}
	activeChunkBuckets[activeIndex] = chunkBuckets[index];
	chunkToActiveChunks[index] = activeIndex;
}

inline void SearchGrid::insertEntity(Entity type, EntitySearchData data)
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

inline void SearchGrid::removeEntity(Entity type, EntitySearchData data)
{
		
}

inline void SearchGrid::

inline bool SearchGrid::checkCollision(Coord tileCoord)
{	
	return tiles->occupieds[world.getTileIndexFromCoord(tileCoord)];
}

inline EntitySearchData SearchGrid::getNearest(Entity e, Coord c)
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

EntityRenderBuffer SearchGrid::getAllInRange(Coord origin, Coord dimensions)
{
	EntityRenderBuffer erd;
	std::vector<uint16_t> chunksOnScreen = getChunksFromArea(origin, dimensions);
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
