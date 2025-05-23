#ifndef TILE_H_
#define TILE_H_
#include "basic.hpp"
#include "mapdimensions.hpp"
#include "categories.hpp"


// DATA OF EVERY GENERATED TILES
// lookup table: hashed coord finds indices, which are indices of every vector containing one attribute
std::unordered_map<std::pair<int, int>, int, hashPair> tileIndices(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);
// reverse of above, gets coords from index
std::vector<std::pair<int, int>> tileCoords(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);

struct TileMoveCost {
	uint8_t up;
	uint8_t down;
	uint8_t left;
	uint8_t right;
};

std::vector<TileMoveCost> adjacentTilesCost(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);
// the cell to which the tile belongs
vector<uint32_t> tileCellIndex;
// the four adjacent tiles' indices in the vectors (ABOVE, RIGHT, BELOW, LEFT)
struct AdjacentTiles {
	int up;
	int down;
	int left;
	int right;
};
vector<AdjacentTiles> adjacentTilesIndices(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);
vector<int> tileAlt(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);
vector<Tile> tileType(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);
vector<Object> tileObject(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);
vector<int> tileObjectAmt(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);
vector<Plant> tilePlant(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);

// seeds (can be tubers or other plant sources) and their linked locations
std::vector<std::pair<int,int>>	seedCoords();
std::vector<Plant> seeds();

/* linked vectors which can be used to determine the variant when the tileObject is a variant and is moved or picked up */
vector<std::pair<float,float>> nearestVariantItem(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<int>	variantItemTypes(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<Grass> tileGrass(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);
vector<bool> tileWater(STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT); //whether a tile has water or not


//FIND NEAR RESOURCES
vector<std::pair<float,float>> nearestWaterTiles(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestLog(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestRocks(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestSand(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestClay(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestDirt(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestStone(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestFlint(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestSalt(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
// vector<std::pair<float,float>> nearestCorpses(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestMilks(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestBeehive(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestSheep(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestFruits(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestGrains(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestVegetables(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestHerbs(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestTextiles(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);

vector<std::pair<float,float>> nearestPlantTiles(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestTreeTiles(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestPlowedTiles(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);
vector<std::pair<float,float>> nearestDirtTiles(STARTING_MAP_HEIGHT * STARTING_MAP_WIDTH);


// SORT TILE METHODS
void ultimateSort(int indexStart) {
	for (int i = indexStart; i < tileIndices.size(); i++) {
		std::pair<int,int> coords = tileCoords[i];
		//WATER TILES
		if (tileType[i] == Tile::ShallowWater || tileType[i] == Tile::DeepWater || tileType[i] == Tile::FlowingWater) {
			tileWater[i] = true;
			nearestWaterTiles.push_back(coords);
			continue;
		}
		//PLANTS
		else if (Plant* plantPtr = std::get_if<Plant>(&tileObject[i])) {
			//WOOD TREES
			for (size_t j = 0; j < woodTrees.size(); j++) {
				if (*plantPtr == woodTrees[j]) { nearestTreeTiles.push_back(coords);
				break; }
			}
			// FRUIT
			for (size_t j = 0; j < fruits.size(); j++) {
				if (*plantPtr == fruits[j]) { nearestFruits.push_back(coords);
				break; }
			}
			//VEGETABLE
			for (size_t j = 0; j < vegetables.size(); j++) {
				if (*plantPtr == vegetables[j]) { nearestVegetables.push_back(coords);
				break; }
			}
			////HERB
			for (size_t j = 0; j < herbs.size(); j++) {
			if (*plantPtr == herbs[j]) { nearestHerbs.push_back(coords);
			break; }
		}
		}
		//SCAVENGEABLES
		else if (Scavengeable* sPtr = std::get_if<Scavengeable>(&tileObject[i])) {
			if (*sPtr == Scavengeable::Beehive) nearestBeehive.push_back(coords);
			else if (*sPtr == Scavengeable::Rock || *sPtr == Scavengeable::Pebble || *sPtr == Scavengeable::LargeRock) nearestRocks.push_back(coords);
			else if (*sPtr == Scavengeable::Log) nearestLog.push_back(coords);
			else if (*sPtr == Scavengeable::Beehive) nearestBeehive.push_back(coords);
			else if (*sPtr == Scavengeable::Flint) nearestFlint.push_back(coords);
		}
		//EXPOSED DIRT
		else {
			bool dirt = false;
			for (int j = 0; j < plowableDirts.size(); j++) {
				if (tileType[i] == plowableDirts[j]) {
					dirt = true;
					//TODO: deal with non-grass tiles, whether dirt tiles count as grass tiles
					if (tileGrass[i] == Grass::NONE) {
						nearestDirtTiles.push_back(coords);
						break;
					}
				}
		}
		for (int j = 0; j < plowedDirts.size(); j++) {
			if (tileType[i] == plowedDirts[j]) {
						dirt = true;
						nearestDirtTiles.push_back(coords);
						break;
				}
			}
		if (!dirt) {
			if (tileType[i] == Tile::Stone) {	nearestStone.push_back(coords); }
	//SALT
		}
		}
		}
}

// sort done to do search for moving objects, like animals and pawns
void movingSort() {

}

// NEAREST NEIGHBOR SEARCH BUILDS
// Define globally
using my_kd_tree_t = nanoflann::KDTreeSingleIndexAdaptor<
    nanoflann::L2_Simple_Adaptor<float, SeedCloud>,
    SeedCloud,
    2
>;

my_kd_tree_t buildSearchTree(vector<std::pair<float,float>> coordinates) {
    SeedCloud tiles;
    tiles.seeds = coordinates;

    my_kd_tree_t tree(2, tiles, {10});
    tree.buildIndex();
    return tree;
}


my_kd_tree_t water = buildSearchTree(nearestWaterTiles);
my_kd_tree_t scavengeable = buildSearchTree(nearestScavengeableTiles);
my_kd_tree_t tree = buildSearchTree(nearestTreeTiles);
my_kd_tree_t stone = buildSearchTree(nearestStoneTiles);
my_kd_tree_t herb = buildSearchTree(nearestHerbTiles);

#endif // TILE_H_
