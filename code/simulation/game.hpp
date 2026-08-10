#include "systems/action/action.hpp"
#include "world/buildable/database.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <core/data.hpp>
#include <core/memory_control.hpp>
#include <simulation/first_spawn.hpp>
#include <simulation/world_gen.hpp>

#include <world/animal/database.hpp>
#include <world/plant/database.hpp>
#include <world/tile/data.hpp>
#include <world/tile/database.hpp>
#include <world/unit/database.hpp>
#include <world/world.hpp>
#include <render/texture.hpp>
#include <render/window.hpp>
#include <render/camera.hpp>
#include <render/draw.hpp>

struct Game
{
  bool first_save = false;
  bool unsaved_changes = true;

  Time absolute_time;
  SDL_Rect player_bounds;      
		
  Arena chunk_arena;
  World world;
  SearchGrid search;

  Arena tile_arena;
  tile::Database tile_database;
  
Arena plant_arena;
plant::Database plant_database;
Arena regrowth_plant_arena;
plant::RegrowthDatabase regrowth_plant_database;
Arena animal_arena;
animal::Database animal_database;
Arena unit_arena;
unit::Database unit_database;
// Arena NPCUnitArena;  
// unit::Database NPCunit::Database;
Arena item_arena;
item::Database item_database;
buildable::Database buildable_database;
Arena buildable_arena;  

void init_new_world();

void deinit_world();

GameSave& save_game(std::string name, GameSave *save);

void load_game(GameSave& save);

void new_game();

void player_spawn();  

void quit();

void handle_event(SDL_Event *e);

void process_world();

uint32_t get_day();  

// =========================
// LOOP
// =========================

void game_loop();

void frame_loop();

void hourly_loop();

void handle_actions_and_movement_loop();    
};

Game* g_game;
