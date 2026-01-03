#include "noiseTools.cpp"
#include "../include/chunk.hpp"

void ChunkDatabase::createChunk() {
  tileDB.addTiles();
}

void ChunkDatabase::activateChunk() {
  
}

void ChunkDatabase::deactivateChunk() {

}

template <typename T>
float blendRegions(T a_r, T a1, T a2, float t1, float t2) {
    float w_r = (1 - t1) * (1 - t2);
    float w_1 = t1 * (1 - t2);
    float w_2 = (1 - t1) * t2;
    float sum = w_r + w_1 + w_2;
    w_r /= sum; w_1 /= sum; w_2 /= sum;
    return a_r * w_r + a1 * w_1 + a2 * w_2;
}

void initializeLocalAltitudeNoise() {
  noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  noise.SetFrequency(0.02f);
  noise.SetFractalType(FastNoiseLite::FractalType_FBm);  
  noise.SetFractalOctaves(4);    
  noise.SetFractalLacunarity(2.0f);
  noise.SetFractalGain(0.5f);
  return noise;
}


alt getTileAltitude(coord regionCoord, coord tileCoord, FastNoiseLite &noise,
                    RegionDatabase &rdb) {
  float tileToRegionRatio = 0.6;
  
  alt thisRegionAlt = rdb.getRegionAltitude(regionCoord);
  coord first = rdb.getNthNearestRegionFromRegion(regionCoord, 1);
  alt nearRegionOneAlt = rdb.getRegionAltitude(first);
  coord second = rdb.getNthNearestRegionFromRegion(regionCoord, 1);
  alt nearRegionTwoAlt = rdb.getRegionAltitude(second);
  std::pair<float, float> weights = rdb.getDistanceWeightFromNearestTwoRegions(region, first, second);
  alt regionAlt = blendRegions(thisRegionAlt, nearRegionOneAlt, nearRegionTwoAlt,
                               weights.first, weights.second);
  alt tileAlt = noiseToAltitude(noise.GetNoise(tileCoord.x, tileCoord.y));
  return lerp(static_cast<float>(tileAlt), static_cast<float>(regionAlt), tileToRegionRatio); 
}


void ChunkDatabase::createChunk(int chunkIndex, RegionDatabase& rdb) {
  for (int x = c.topLeftCorner.x; x < c.topLeftCorner.x + width; x++) {
    for (int y = c.topLeftCorner.y; y < c.topLeftCorner.y + height; y++) {
      coord tileCoord = {x, y};
      coord regionCoord = rdb.getRegionFromTile(tileCoord);
      getTileAltitude(regionCoord, tileCoord, noise, rdb);
    }
  }
}

coord ChunkDatabase::getChunkCoord(coord tile) {
        if (tile.x > WORLD_WIDTH)
          tile.x = tile.x % chunkWidth;
	if (tile.y > WORLD_HEIGHT) tile.y = tile.y % chunkHeight;
	return {tile.x / chunkWidth, tile.y / chunkHeight };
      }

coord ChunkDatabase::getRelativeTileCoord(coord tileCoord) {
	return {tileCoord.x % chunkWidth, tileCoord.y % chunkHeight};
      }

alt ChunkDatabase::getAltDifference(coord t1, coord t2) {
        coord c1 = getChunkCoord(t1);
        coord c2 = getChunkCoord(t2);
        coord r1 = getRelativeTileCoord(t1);
	coord r2 = getRelativeTileCoord(t2);
        int first = chunks[c1.y][c1.x].tileDB.[r1.y][r1.x].altitude;
        int second = chunks[c2.y][c2.x].tileDB.[r2.y][r2.x].altitude;
	return first - second;
      }

// returns same tile if none are lower
      coord 
      ChunkDatabase::getLowestAdjacentTileLowerThanTile(coord centerTile) {
	coord chunkCoord = getChunkCoord(centerTile);
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    alt lowestAlt = chunks[chunkCoord.y][chunkCoord.x].altitude;
    coord ret = centerTile;

       for (int i = 0; i < 4; i++) {
        int nx = centerTile.x + dx[i];
        int ny = centerTile.y + dy[i];

	coord cc = getRelativeTileCoord(centerTile);
        coord ncc = getChunkCoord(nx, ny);

	alt adjAlt = chunks[ncc.y][ncc.x].tileDB.tiles[ny][nx].altitude;

        if (adjAlt <= lowestAlt) {
          if (adjAlt == lowestAlt) {
            if (ret == centerTile || rchance(0.25)) {
              ret = {nx, ny};
	      lowestAlt = adjAlt;
            }
	  }  else {
            ret = {nx, ny};
            lowestAlt = adjAlt;
	  } 
          }
        }
       }       
      return ret;
    }
}

float riverTileVol = 0.2;

// todo: have to make it so that water mechanics are simple and discrete, and
// that player can manipulate them in the same way they work naturally. cheap
// way to process tiles so that snow melting forms rivers which may evaporate
// during certain seasons.
// todo: every tile stores a bool 
// TODO:: have this make a water fall if alt difference + certain conditions are met. 
void ChunkDatabase::riverCreate(coord riverStart, float64_t riverVol) {
  // base case: river vol has run out
  if (riverVol < 0) {
    return;
  }

  coord lowest = getLowestAdjacentTileLowerThanTile(riverStart);
  //volume must be lost more if 
  if (lowest == riverStart) 
  riverVol -= riverTileVol;
  // the river loses volume based on how much it needs to fill up a certain
  // tile.
  
  
  
  
  if (tiles[riverStart.x][riverStart.y].alitude < tiles[
}
