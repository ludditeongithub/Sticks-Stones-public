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
  bool firstSave = false;
  bool unsavedChanges = true;

  Time absoluteTime;
  SDL_Rect playerBounds;      
		
  Arena chunkArena;
  World world;
  SearchGrid search;

Arena plantArena;
PlantDatabase plantDatabase;
Arena regrowthPlantArena;
RegrowthPlantDatabase regrowthPlantDatabase;
Arena animalArena;
AnimalDatabase animalDatabase;
Arena unitArena;
UnitDatabase unitDatabase;
// Arena NPCUnitArena;  
// UnitDatabase NPCUnitDatabase;
Arena itemArena;
ItemDatabase itemDatabase;
BuildableDatabase buildableDatabase;
Arena buildableArena;  

void init_new_world();

void deinit_world();

GameSave& save_game(std::string name, GameSave *save);

void load_game(GameSave& save);

void new_game();

void player_spawn();  

void quit();

void handle_event(SDL_Event *e);

void process_world();

void game_loop();

void frame_loop();

void hourly_loop();  

uint32_t get_day();
};

Game* g_game;
