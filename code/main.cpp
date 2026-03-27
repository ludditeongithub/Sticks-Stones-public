#include <core/entity.hpp>
#include <core/memory.hpp>
#include <core/memory_control.hpp>
#include <cstdint>
#include <render/texture.hpp>
#include <render/window.hpp>
#include <render/camera.hpp>
#include <render/draw.hpp>
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

int startGame()
{
	initWindow() ?: printf("Init failed.");

	loadMedia();

	//	GameOptions go = selectGameOptions();

	// NOTE: right now Ws uses regions while world does chunks, but the same width
	// and height is used for both.
	WorldSpawner *ws = new WorldSpawner(50 / 2, 50 / 2);
	ws->generateWorld();

	Arena* chunkArena =
	    new Arena(World::ENTITY_SIZE * (ws->WIDTH_WITH_BORDER + ws->HEIGHT_WITH_BORDER) *
		      CHUNKS_PER_REGION);
	World world(chunkArena, 50, 50);
	world.loadChunkData(*ws);

	Arena* tileArena = new Arena(TileDatabase::ENTITY_SIZE * world.WORLD_TILE_AMOUNT);
	TileDatabase tileDatabase(tileArena, ws->tsb, world);

	SearchGrid search(world);

	Arena *plantArena =
	    new Arena(PlantDatabase::ENTITY_SIZE * ws->psb.size * PLANT_ALLOC_FACTOR);
	PlantDatabase plantDatabase(plantArena, search, ws->psb.size * PLANT_ALLOC_FACTOR);

	Arena *animalArena =
	    new Arena(AnimalDatabase::ENTITY_SIZE * ws->asb.size * ANIMAL_ALLOC_FACTOR);
	AnimalDatabase animalDatabase(animalArena, ws->asb.size * ANIMAL_ALLOC_FACTOR, search);
	animalDatabase.addAnimals(ws->asb);

	gSpriteSheetTexture.loadFromFile("sprite_sheet.png");

	Arena *unitArena = new Arena(UnitDatabase::ENTITY_SIZE * UNIT_CAP);
	UnitDatabase unitDatabase(UNIT_CAP);

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
		unitDatabase.birthUnit(tileCoord);
	}

	drawEntities(world, leftCornerTile, tileDatabase.tiles, animalDatabase.ages,
		     animalDatabase.frames, animalDatabase.statuses, unitDatabase.frames,
		     unitDatabase.ages, unitDatabase.frameDatas, search);
}	

int main()
{
		WorldSpawner ws(200, 200);
		ws.generateWorld();
		ws.printInfo();	
}
