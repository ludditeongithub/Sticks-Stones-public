#pragma once
#include <unordered_map>
#include <vector>
#include <stack>

#include <core/data.hpp>
#include <core/entity.hpp>
#include <core/memory.hpp>
#include <core/containers.hpp>

#include <world/tile/data.hpp>
#include <world/chunk/data.hpp>
#include <world/unit/enum.hpp>
#include <world/animal/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/item/enum.hpp>

 struct GridInfo {
    uint16_t index;
    uint16_t distance;
 };

 // certain biomes may need larger search grids
// SearchGrid itself should be an indexed data structure 
 struct SearchGrid {
   constexpr SearchGrid() {};
   
   constexpr NATURAL_CHUNK_SEARCH_SIZE = (AVERAGE_CHUNK_PLANTS_SIZE +
                                         AVERAGE_CHUNK_ANIMALS_SIZE +
					  AVERAGE_CHUNK_ITEM_SIZE) * 1.25;
   constexpr ACTIVE_CHUNK_SEARCH_SIZE = (AVERAGE_CHUNK_PLANTS_SIZE +
                                         AVERAGE_CHUNK_ANIMALS_SIZE +
     AVERAGE_CHUNK_CIVILIZATION_ITEM_SIZE + AVERAGE_CHUNK_UNIT_SIZE) * 1.25;

   using ChunkBucket = std::unordered_map<Entity, std::vector<EntitySearchData>>;

   // stores unitIndex, if unit is to be wiped later due to not actually being
   // in bucket anymore
   Arena *chunkBucketArena;
   Arena *activeBucketArena;

   Array<ChunkBucket *> chunkBuckets;
   Array<ChunkBucket *> activeChunkBuckets;
   std::stack<size_t> freeIndices;
   Array<size_t> activeChunks;
   Array<std::vector<bool> *> occupiedTiles;   

   // to begin with, all chunks are given the default amount of memory. active chunks and super-active chunks are upgraded to higher amounts of memory
   SearchGrid(size_t chunkAmount);

   size_t estimatedActiveChunkAmount(size_t chunkAmount) {
     return chunkAmount * 0.01;
   }

   void addActiveChunk(size_t index);   

   inline GridInfo getNthNearestChunk(Coord c, uint16_t n);

   void reset(); 

  inline void insertEntity(Coord tileCoord, Entity type,
                           EntitySearchData data);

   inline bool checkCollision(Coord tileCoord);

  // inline void setOldEntity(Coord tileCoord, uint16_t index) {
  //   size_t gc = getChunkIndexFromTile(tileCoord);
    
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
