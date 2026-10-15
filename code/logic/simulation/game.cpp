#include "game.hpp"
#include "core/saves.hpp"
#include "data/run/item_database.hpp"
#include "logic/simulation/launch_game.hpp"
#include "logic/simulation/save_game.hpp"
#include <data/const/database.hpp>
#include <data/run/tile_database.hpp>

void Game::start()
{
		speed = 1;
}

void Game::init_new_world()
{
	absolute_time = 0;
	WorldSpawner *ws = new WorldSpawner(50 / 2, 50 / 2);
	ws->generate_empty_world();
	ws->spawn_entities();
	world.load_chunk_data(*ws);
        
	arena = Arena((tile::Database::ENTITY_SIZE * coord::tile_amount) +
				(plant::Database::ENTITY_SIZE * plant::CAPACITY) +
				(animal::Database::ENTITY_SIZE * animal::CAPACITY) +
                      (unit::Database::ENTITY_SIZE * unit::CAPACITY));

	init_databases();

	tile_database.add_generated_tiles(ws->tile_spawn_buffer);
	//variant_item_database item::VariantDatabase(item_database);
	plant_database.add_plants(ws->plant_spawn_buffer);
	// animal_database.init(&arena, animal::CAPACITY, search, tile_database,
	// variant_item_database); animal_database.add_animals(ws->animal_spawn_buffer);
}

void Game::init_databases()
{
  tile_database.init(&arena, coord::tile_amount);
        item_database.init(&arena, item::CAPACITY, search, tile_database);
        plant_database.init(&arena, plant::CAPACITY, search, tile_database);
}

void Game::save_game(std::string name, GameSave* save)
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
  save.load_and_init_memory(*this);
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
	// NOTE: may have to close main menu.
	init_new_world();
	start();
}

void Game::handle_event(SDL_Event *e)
{
	
}
