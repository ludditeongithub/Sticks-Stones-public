#include "game.hpp"
#include "core/saves.hpp"
#include "logic/simulation/game_time.hpp"
#include "logic/simulation/launch_game.hpp"
#include "logic/simulation/save_game.hpp"
#include "data/run/unit_database.hpp"
#include <optional>

void Game::start()
{
		speed = 1;
		while () game_loop();				
}

void Game::init_new_world()
{
	absolute_time = 0;
	WorldSpawner *ws = new WorldSpawner(50 / 2, 50 / 2);
	ws->generate_empty_world();
	ws->spawn_entities();

	chunk_arena =
	    Arena(World::ENTITY_SIZE * (ws->WIDTH_WITH_BORDER + ws->HEIGHT_WITH_BORDER) * CHUNKS_PER_REGION);
	world = World(chunk_arena, 50, 50);
	world.load_chunk_data(*ws);

	tile_arena = Arena(tile::Database::ENTITY_SIZE * world.WORLD_TILE_AMOUNT);
	tile_database = tile::Database(tile_arena, ws->tile_spawn_buffer, world);

	search(world);
	
	plant_arena = Arena(plant::Database::ENTITY_SIZE * PLANT_DATABASE_CAP);
	plant_database = plant::Database(&plant_arena, search, PLANT_DATABASE_CAP);

	animal_arena = Arena(animal::Database::ENTITY_SIZE * ANIMAL_DATABASE_CAP);
	animal_database = animal::Database(&animal_arena, ANIMAL_DATABASE_CAP, search);
	animal_database->add_animals(ws->animal_spawn_buffer);	

	player_unit_arena = Arena(unit::Database::ENTITY_SIZE * UNIT_CAP);
	player_unit_database = unit::Database(player_unit_arena, PLAYER_UNIT_DATABASE_CAP, world, search);

	NPCUnitArena = Arena(unit::Database::ENTITY_SIZE * NPC_UNIT_DATABASE_CAP);
        NPCunit::Database = unit::Database(NPCUnitArena, NPC_UNIT_DATABASE_CAP, world, search);

        sprite_sheet_texture.load_from_file("sprite_sheet.png");
}

GameSave& Game::save_game(std::string name, GameSave* save)
{
		bool successful = false;
  if (save == nullptr)
  {
		  save = new GameSave(name);
		  successful = true;		  
  }
  else
  {                   
		  successful = save->confirm_save(); // TODO: print urgent box "Overwrite"
  }
  if (successful) save->save(*this);
}

void Game::load_game(GameSave& save)
{
  // TODO: init and loading can be different if entities exceed maximum size
		init_new_world();
		save.load(*this);
}

void Game::deinit_world()
{
  
}

void Game::player_spawn()
{
  
}

void Game::new_game()
{
	//	GameOptions go = select_game_options();

	// NOTE: right now Ws uses regions while world does chunks, but the same width
	// and height is used for both.
	
}

void Game::handle_event(SDL_Event *e)
{
	for (size_t i = 0; i < ui.buttons.size(); i++) ui.buttons[i].handle_event(e);
}
