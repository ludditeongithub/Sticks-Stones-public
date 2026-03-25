#ifndef TILE_H_
#define TILE_H_
#include <vector>

// DATA OF EVERY GENERATED TILES
// TODO: make tile be found from chunk
// // lookup table: hashed coord finds indices, which are indices of every vector containing one
// attribute std::unordered_map<std::pair<int, int>, int, hashPair> tileIndices(STARTING_MAP_WIDTH *
// STARTING_MAP_HEIGHT);
// // reverse of above, gets coords from index
// std::vector<std::pair<int, int>> tileCoords(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);

// TODO: make move cost derived, not stored
// struct TileMoveCost {
// 	uint8_t up;
// 	uint8_t down;
// 	uint8_t left;
// 	uint8_t right;
// };

// std::vector<TileMoveCost> adjacentTilesCost(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);
// // the cell to which the tile belongs
// // TODO: checker to see if adjacent tile cells are out of bound upon movement
vector<uint32_t> tileCellIndex;

// the four adjacent tiles' indices in the vectors (ABOVE, RIGHT, BELOW, LEFT)
struct AdjacentTiles
{
	int up;
	int down;
	int left;
	int right;
};

std::vector<AdjacentTiles> adjacentTilesIndices(STARTING_MAP_WIDTH *STARTING_MAP_HEIGHT);

/* linked vectors which can be used to determine the variant when the tileObject is a variant and is
 * moved or picked up */

std::vector<bool>
tileWater(STARTING_MAP_WIDTH *STARTING_MAP_HEIGHT); // whether a tile has water or not

// FIND NEAR RESOURCES

class TileDatabase
{
      private:
	static coord &topLeftCorner;

	std::vector<std::vector<TileInfo>> tiles;

      public:
	TileDatabase(uint32_t regionID, std::vector<std::vector<uint16_t>> altitudeMap,
		     std::vector<std::vector<Tile>> tileMap) {

	};

	void addTiles(std::vector<std::vector<Tile>> tiles, std::vector<Grass> tileGrass,
		      std::vector<std::vector<uint16_t>> altitudes,
		      std::vector<std::vector<Biome>> tileBiome);
	const Tile getTile(int x, int y);
	const uint16_t getTileAltitude(int x, int y);
	const Biome getTileBiome(int x, int y);

	int getBottomBorder() { return topLeftCorner.y + chunkHeight; };
	int getTopBorder() { return topLeftCorner.y; };
	int getRightBorder() { return topLeftCorner.x + chunkWidth; };
	int getLeftBorder() { return topLeftCorner.x; };
};

#endif // TILE_H_
