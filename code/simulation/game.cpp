#include "game.hpp"
#include "core/saves.hpp"
#include "simulation/game_time.hpp"
#include "simulation/launch_game.hpp"
#include "simulation/saveGame.hpp"
#include "world/unit/database.hpp"
#include <optional>

void Game::initNewWorld()
{
	absoluteTime = 0;
	WorldSpawner *ws = new WorldSpawner(50 / 2, 50 / 2);
	ws->generateWorld();

	chunkArena =
	    Arena(World::ENTITY_SIZE * (ws->WIDTH_WITH_BORDER + ws->HEIGHT_WITH_BORDER) * CHUNKS_PER_REGION);
	world = World(chunkArena, 50, 50);
	world.loadChunkData(*ws);

	tileArena = Arena(TileDatabase::ENTITY_SIZE * world.WORLD_TILE_AMOUNT);
	tileDatabase = TileDatabase(tileArena, ws->tileSpawnBuffer, world);

	search(world);
	
	plantArena = Arena(PlantDatabase::ENTITY_SIZE * PLANT_DATABASE_CAP);
	plantDatabase = PlantDatabase(&plantArena, search, PLANT_DATABASE_CAP);

	animalArena = Arena(AnimalDatabase::ENTITY_SIZE * ANIMAL_DATABASE_CAP);
	animalDatabase = AnimalDatabase(&animalArena, ANIMAL_DATABASE_CAP, search);
	animalDatabase->addAnimals(ws->animalSpawnBuffer);	

	playerUnitArena = Arena(UnitDatabase::ENTITY_SIZE * UNIT_CAP);
	playerUnitDatabase = UnitDatabase(playerUnitArena, PLAYER_UNIT_DATABASE_CAP, world, search);

	NPCUnitArena = Arena(UnitDatabase::ENTITY_SIZE * NPC_UNIT_DATABASE_CAP);
        NPCUnitDatabase = UnitDatabase(NPCUnitArena, NPC_UNIT_DATABASE_CAP, world, search);

        spriteSheetTexture.loadFromFile("sprite_sheet.png");
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

void Game::playerSpawn()
{
  
}

void Game::newGame()
{
	//	GameOptions go = selectGameOptions();

	// NOTE: right now Ws uses regions while world does chunks, but the same width
	// and height is used for both.
	
	
}

void Game::handleEvent(SDL_Event *e)
{
	for (size_t i = 0; i < ui.buttons.size(); i++) ui.buttons[i].handleEvent(e);
}
