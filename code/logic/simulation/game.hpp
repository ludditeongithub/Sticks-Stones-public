#pragma once
#include "data/run/buildable_database.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <core/memory_control.hpp>
#include <logic/simulation/world_gen.hpp>
#include <data/run/animal_database.hpp>
#include <data/run/plant_database.hpp>
#include <data/const/tile_data.hpp>
#include <data/run/tile_database.hpp>
#include <data/run/unit_database.hpp>
#include <data/run/world.hpp>
#include <display/render/texture.hpp>
#include <display/render/screen.hpp>
#include <display/render/camera.hpp>
#include <display/render/draw.hpp>

struct GameSave;

struct Game
{
  bool first_save = false;
  bool unsaved_changes = true;
  int8_t speed = 1;

  Time absolute_time;
  SDL_Rect player_bounds;      
		
  World world;
  SearchGrid search;

  Arena arena;

tile::Database tile_database;  
plant::Database plant_database;
plant::RegrowthDatabase regrowth_plant_database;
animal::Database animal_database;
unit::Database unit_database;
// Arena NPCUnitArena;  
// unit::Database NPCunit::Database;
item::Database item_database;
buildable::Database buildable_database;

Game(size_t world_width, size_t world_height);
		
void init_new_world();

void deinit_world();

GameSave& save_game(std::string name, GameSave *save);

void load_game(GameSave& save);

void new_game();

void start();

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
