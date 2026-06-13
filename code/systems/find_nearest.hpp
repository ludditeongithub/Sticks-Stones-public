#pragma once
#include "world/tile/database.hpp"
#include <cstdint>
#include <stack>
#include <unordered_map>
#include <vector>

#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/entity.hpp>
#include <core/memory.hpp>

#include <world/animal/enum.hpp>
#include <world/chunk/data.hpp>
#include <world/item/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/tile/data.hpp>
#include <world/unit/enum.hpp>
#include <world/world.hpp>

struct GridInfo
{
	uint16_t index;
	uint16_t distance;
};

constexpr uint16_t AVERAGE_CHUNK_PLANTS_SIZE = CHUNK_SIZE / 2.5;
constexpr uint16_t AVERAGE_CHUNK_ANIMALS_SIZE = CHUNK_SIZE / 15;
constexpr uint16_t AVERAGE_CHUNK_SCAVENGEABLE_SIZE = CHUNK_SIZE / 12;
constexpr uint16_t AVERAGE_CHUNK_CIVILIZATION_ITEM_SIZE = CHUNK_SIZE / 10;
constexpr uint16_t AVERAGE_CHUNK_UNIT_SIZE = CHUNK_SIZE / 25;

constexpr uint16_t NATURAL_CHUNK_SEARCH_SIZE =
    (AVERAGE_CHUNK_PLANTS_SIZE + AVERAGE_CHUNK_ANIMALS_SIZE + AVERAGE_CHUNK_SCAVENGEABLE_SIZE) *
    1.25;

constexpr uint16_t ACTIVE_CHUNK_SEARCH_SIZE =
    (AVERAGE_CHUNK_PLANTS_SIZE + AVERAGE_CHUNK_ANIMALS_SIZE + AVERAGE_CHUNK_SCAVENGEABLE_SIZE +
     AVERAGE_CHUNK_CIVILIZATION_ITEM_SIZE + AVERAGE_CHUNK_UNIT_SIZE) *
    1.30;

// certain biomes may need larger search grids
// SearchGrid itself should be an indexed data structure
struct SearchGrid
{
	World& world;

	SearchGrid(World& world);

	using ChunkBucket = std::unordered_map<Entity, std::vector<EntitySearchData>>;

	// stores unitIndex, if unit is to be wiped later due to not actually being
	// in bucket anymore
	Arena *chunkBucketArena;
	Arena *activeBucketArena;

	Array<ChunkBucket *> chunkBuckets;
	Array<ChunkBucket *> activeChunkBuckets;
	std::unordered_map<uint16_t, uint16_t> chunkToActiveChunks;
	std::stack<uint16_t> freeIndices;
	std::vector<bool> activeChunks;
	uint32_t activeCount;
	TileDatabase& tiles;

	// to begin with, all chunks are given the default amount of memory. active chunks and
	// super-active chunks are upgraded to higher amounts of memory

	uint16_t getActiveChunkIndex(uint16_t index);

	void addActiveChunk(uint16_t index);

	inline GridInfo getNthNearestChunk(Coord c, uint16_t n);

	void reset();

  //OPTI: only have buckets be per chunk, moving entities only move when moving between chunks 
        inline void insertEntity(Entity type, EntitySearchData data);
        inline void removeEntity(Entity type, EntitySearchData data);
        inline void moveEntity(Entity type, EntitySearchData data);

	inline bool checkCollision(Coord tileCoord);

	inline EntitySearchData getNearest(Entity e, Coord c);
	inline EntitySearchData getNearestWithinRange(Entity e, Coord c, uint16_t maxRange);

	inline Array<EntitySearchData> getAllOFTypeInRange(Entity e, Coord o, Coord d);

	inline EntityRenderBuffer getAllInRange(Coord o, Coord d);
	// inline void setOldEntity(Coord tileCoord, uint16_t index) {
	//   uint16_t gc = getChunkIndexFromTile(tileCoord);

	//   fchunkBuckets[gc].size(); i++) if (indices[i] == index) old[i] = 1;
	// }

	// inline void removeOldEntities() {
	//   for (int i = 0; i < chunkBuckets.size(); i++) {
	//     auto* old = chunkBuckets[i].column<1>();
	//     auto* indices = chunkBuckets[i].column<0>();

	//     std::vector<uint16_t> a(chunkBuckets[i].size());
	//     int k = -1;
	//     for (int j = 0; j < chunkBuckets[i].size(); j++) {
	//       if (old[j] == 0) a[k++] = indices[j];
	//     }
	//     chunkBuckets[i].clear();
	//     chunkBuckets[i].reserve(k);
	//     old = chunkBuckets[i].column<1>();
	//     indices = chunkBuckets[i].column<0>();
	//     for (int j = 0; j < k; j++) {
	// 	chunkBuckets[i].emplace_back(a[j], false);
	//     }
	//   }
	// }
};
