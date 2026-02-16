#include "find_nearest.hpp"

SearchGrid::SearchGrid(size_t chunkAmount) {
     chunkBucketArena = new Arena(
         (chunkAmount * NATURAL_CHUNK_SEARCH_SIZE));

     activeBucketArena = new Arena(
         (chunkAmount * NATURAL_CHUNK_SEARCH_SIZE) +
         (estimatedActiveChunkAmount(chunkAmount) * ACTIVE_CHUNK_SEARCH_SIZE));
     
     for (size_t i = 0; i < chunkAmount; i++) {
       chunkBuckets[i] =
	 arena_make_array<ChunkBucket>(chunkBucketArena, NATURAL_CHUNK_SEARCH_SIZE);
       activeChunks[i] = false;
       occupiedTiles[i]->reserve(CHUNK_SIZE);
       for (size_t j = 0; j < CHUNK_SIZE; j++) occupiedTiles[i][j].emplace_back(false);
     }
}

inline GridInfo SearchGrid::getNthNearestChunk(Coord c, uint16_t n) {
    const uint16_t center = getChunkFromTile(c);
    const int ha = c.x % CHUNK_SIZE;
    const int va = c.y % CHUNK_SIZE;
    const int distN = va;
    const int distS = CHUNK_SIZE - va;
    const int distW = ha;
    const int distE = CHUNK_SIZE - ha;

    struct Entry {
        uint16_t dist;
        int16_t offset;
    };

    constexpr int row = LENGTH_CHUNKS;

    Entry neighbors[8] = {
        { static_cast<uint16_t>(distN),         -row     },
        { static_cast<uint16_t>(distS),          row     },
        { static_cast<uint16_t>(distW),         -1       },
        { static_cast<uint16_t>(distE),          1       },
        { static_cast<uint16_t>(distN + distE), -row + 1 },
        { static_cast<uint16_t>(distN + distW), -row - 1 },
        { static_cast<uint16_t>(distS + distE),  row + 1 },
        { static_cast<uint16_t>(distS + distW),  row - 1 }
    };

    const uint16_t idx = n & 7;

    std::nth_element(
        std::begin(neighbors),
        std::begin(neighbors) + idx,
        std::end(neighbors),
        [](const Entry& a, const Entry& b) {
            return a.dist < b.dist;
        }
    );

    const int target = int(center) + neighbors[idx].offset;

    GridInfo result;
    result.index = (target >= 0 && target < CHUNK_AMOUNT)
                   ? static_cast<uint16_t>(target)
                   : center;
    result.distance = neighbors[idx].dist;

    return result;  
}

 void SearchGrid::addActiveChunk(size_t index) {
     activeChunks[index] = true;
     size_t activeIndex;
     if (freeIndices.empty()) activeIndex = activeChunks.count;
     else {
       activeIndex = freeIndices.top();
       freeIndices.pop();
     }       
     activeChunkBuckets[activeIndex] = chunkBuckets[index];
 }

 inline void SearchGrid::insertEntity(Coord tileCoord, Entity type,
                           EntitySearchData data) {
    size_t gc = getChunkIndexFromTile(tileCoord);
    size_t i = getTileIndexChunkRelative(tileCoord);    
    if (!(*occupiedTiles[gc])[i]) {    
      if (activeChunks[gc]) {
	activeChunkBuckets[gc].at(type).push_back(data);
      } else {
	chunkBuckets[gc].at(type).push_back(data);
      }            
    }
  }

 inline bool SearchGrid::checkCollision(Coord tileCoord) {
    size_t gc = getChunkIndexFromTile(tileCoord);
    size_t i = getTileIndexChunkRelative(tileCoord);    
    return occupiedTiles[gc][i];	   
  }

//inline void SearchGrid


