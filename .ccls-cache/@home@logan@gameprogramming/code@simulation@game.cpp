#include "game.hpp"
#include "core/saves.hpp"
#include "simulation/saveGame.hpp"
#include <optional>

void Game::initNewWorld()
{
	absoluteTime = 0;
	WorldSpawner *ws = new WorldSpawner(50 / 2, 50 / 2);
	ws->generateWorld();

	chunkArena =
	    Arena(World::ENTITY_SIZE * (ws->WIDTH_WITH_BORDER + ws->HEIGHT_WITH_BORDER) *
		      CHUNKS_PER_REGION);
	world = World(chunkArena, 50, 50);
	world.loadChunkData(*ws);

	tileArena = Arena(TileDatabase::ENTITY_SIZE * world.WORLD_TILE_AMOUNT);
	tileDatabase = TileDatabase(tileArena, ws->tsb, world);

	search(world);
	
	plantArena = Arena(PlantDatabase::ENTITY_SIZE * ws->plantSpawnBuffer.size * PLANT_ALLOC_FACTOR);
	plantDatabase = PlantDatabase(&plantArena, search, ws->plantSpawnBuffer.size * PLANT_ALLOC_FACTOR);

	animalArena = Arena(AnimalDatabase::ENTITY_SIZE * ws->asb.size * ANIMAL_ALLOC_FACTOR);
	animalDatabase = AnimalDatabase(&animalArena, ws->asb.size * ANIMAL_ALLOC_FACTOR, search);
	animalDatabase->addAnimals(ws->asb);

	spriteSheetTexture.loadFromFile("sprite_sheet.png");

	unitArena = Arena(UnitDatabase::ENTITY_SIZE * UNIT_CAP);
	unitDatabase = UnitDatabase(unitArena, UNIT_CAP, world, search);
}

GameSave& Game::saveGame(std::string name, GameSave* save)
{
		bool successful = false;
  if (save == nullptr)
  {
		  save = new GameSave(name);
		  successful = true;		  
  }
  else
  {                   
		  successful = save->confirmSave(); // TODO: print urgent box "Overwrite"
  }
  if (successful) save->save(*this);
}

void Game::loadGame(GameSave& save)
{
  // TODO: init and loading can be different if entities exceed maximum size
		initNewWorld();
		save.load(*this);
}

void Game::deinitWorld()
{
	
}	

void Game::newGame()
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
		unitDatabase->birthUnit(tileCoord);
	}
}

void Game::handleEvent(SDL_Event *e)
{
	for (size_t i = 0; i < ui.buttons.size(); i++) ui.buttons[i].handleEvent(e);
}
