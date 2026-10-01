#include "game.hpp"
#include "core/saves.hpp"
#include "logic/simulation/launch_game.hpp"
#include "logic/simulation/save_game.hpp"
#include <data/const/database.hpp>
#include <data/run/tile_database.hpp>

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
	world.load_chunk_data(*ws);

	arena = Arena((tile::Database::ENTITY_SIZE * world.world_tile_amount) +
				(plant::Database::ENTITY_SIZE * plant::CAPACITY) +
				(animal::Database::ENTITY_SIZE * animal::CAPACITY) +
                      (unit::Database::ENTITY_SIZE * unit::CAPACITY));

	tile_database = tile::Database(&arena, world.world_tile_amount);
        plant_database = plant::Database(&arena, plant::CAPACITY, search, tile_database);
	animal_database = animal::Database(&arena, animal::CAPACITY, search);
	animal_database->add_animals(ws->animal_spawn_buffer);	


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
