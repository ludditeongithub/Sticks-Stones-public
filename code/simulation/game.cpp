#include <core/data.hpp>
#include <core/memory_control.hpp>
#include <simulation/first_spawn.hpp>
#include <simulation/world_gen.hpp>
#include <systems/find_nearest.hpp>
#include <ui/state.hpp>
#include <world/animal/entity.hpp>
#include <world/plant/entity.hpp>
#include <world/tile/data.hpp>
#include <world/tile/database.hpp>
#include <world/unit/entity.hpp>
#include <world/world.hpp>
#include <render/texture.hpp>
#include <render/window.hpp>
#include <render/camera.hpp>
#include <render/draw.hpp>

void startGame()
{
	
}

void startGame()
{

}	

struct Game
{
Time absoluteTime;
World world;
SearchGrid search;
Arena tileArena;
TileDatabase tileDatabase;
std::vector<Arena> plantArenas;
std::vector<PlantDatabase> plantDatabases;
std::vector<Arena> animalArenas;
std::vector<AnimalDatabase> animalDatabases;
std::vector<Arena> unitArenas;
std::vector<UnitDatabase> unitDatabases; 

void initWorld()
{
	absoluteTime = 0;
	WorldSpawner *ws = new WorldSpawner(50 / 2, 50 / 2);
	ws->generateWorld();

	Arena* chunkArena =
	    new Arena(World::ENTITY_SIZE * (ws->WIDTH_WITH_BORDER + ws->HEIGHT_WITH_BORDER) *
		      CHUNKS_PER_REGION);
	world = new World(chunkArena, 50, 50);
	world.loadChunkData(*ws);

	Arena* tileArena = new Arena(TileDatabase::ENTITY_SIZE * world.WORLD_TILE_AMOUNT);
	tileDatabase = new TileDatabase(tileArena, ws->tsb, world);

	SearchGrid search(world);

	plantArenas.push_back(Arena(PlantDatabase::ENTITY_SIZE * ws->psb.size * PLANT_ALLOC_FACTOR));
	plantDatabases.push_back(PlantDatabase(&plantArenas[0], search, ws->psb.size * PLANT_ALLOC_FACTOR));

	animalArenas.push_back( Arena(AnimalDatabase::ENTITY_SIZE * ws->asb.size * ANIMAL_ALLOC_FACTOR));
	animalDatabases.push_back(AnimalDatabase(&animalArenas[0], ws->asb.size * ANIMAL_ALLOC_FACTOR, search));
	animalDatabases[0].addAnimals(ws->asb);

	gSpriteSheetTexture.loadFromFile("sprite_sheet.png");

	unitArenas.push_back(Arena(UnitDatabase::ENTITY_SIZE * UNIT_CAP));
	unitDatabases.push_back(UNIT_CAP);
}

void deinitWorld()
{
	absoluteTime = 0;
	WorldSpawner *ws = new WorldSpawner(50 / 2, 50 / 2);
	ws->generateWorld();

	Arena* chunkArena =
	    new Arena(World::ENTITY_SIZE * (ws->WIDTH_WITH_BORDER + ws->HEIGHT_WITH_BORDER) *
		      CHUNKS_PER_REGION);
	world = new World(chunkArena, 50, 50);
	world.loadChunkData(*ws);

	Arena* tileArena = new Arena(TileDatabase::ENTITY_SIZE * world.WORLD_TILE_AMOUNT);
	tileDatabase = new TileDatabase(tileArena, ws->tsb, world);

	SearchGrid search(world);

	plantArenas.push_back(Arena(PlantDatabase::ENTITY_SIZE * ws->psb.size * PLANT_ALLOC_FACTOR));
	plantDatabases.push_back(PlantDatabase(&plantArenas[0], search, ws->psb.size * PLANT_ALLOC_FACTOR));

	animalArenas.push_back( Arena(AnimalDatabase::ENTITY_SIZE * ws->asb.size * ANIMAL_ALLOC_FACTOR));
	animalDatabases.push_back(AnimalDatabase(&animalArenas[0], ws->asb.size * ANIMAL_ALLOC_FACTOR, search));
	animalDatabases[0].addAnimals(ws->asb);

	gSpriteSheetTexture.loadFromFile("sprite_sheet.png");

	unitArenas.push_back(Arena(UnitDatabase::ENTITY_SIZE * UNIT_CAP));
	unitDatabases.push_back(UNIT_CAP);
}	

void newGame()
{
	//	GameOptions go = selectGameOptions();

	// NOTE: right now Ws uses regions while world does chunks, but the same width
	// and height is used for both.
	
	Coord chunkStart = world.getRandomPlayerStart();
	uint32_t startChunkIndex = getChunkIndex(chunkStart);
	Coord leftCornerTile = getChunkLeftCornerTile(chunkStart);
	uint16_t startingUnits = 10;
	for (size_t i = 0; i < startingUnits; i++)
	{
		bool foundTile = false;
		uint32_t tile;
		while (!foundTile)
		{
			tile = world.getTileIndexFromCoord(
				{leftCornerTile.x + static_cast<uint16_t>(CHUNK_LENGTH * random_chance->next()),
			     leftCornerTile.y + CHUNK_LENGTH});
			if (!tileDatabase.occupieds[tile])
				foundTile = true;
		}
		Coord tileCoord = world.getTileCoordFromIndex(tile);
		unitDatabases[0].birthUnit(tileCoord);
	}
}

void gameLoop()
{

	
	drawEntities(world, leftCornerTile, tileDatabase.tiles, animalDatabases[0].ages,
		     animalDatabases[0].frames, animalDatabases[0].statuses, unitDatabases[0].frames,
		     unitDatabases[0].ages, unitDatabases[0].frameDatas, search);
}	

};


	
