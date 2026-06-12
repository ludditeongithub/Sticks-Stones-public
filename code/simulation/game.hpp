#include "world/buildable/entity.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <core/data.hpp>
#include <core/memory_control.hpp>
#include <simulation/first_spawn.hpp>
#include <simulation/world_gen.hpp>
#include <systems/find_nearest.hpp>
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

struct Game
{
  bool firstSave = false;
  bool unsavedChanges = true;
  
Time absoluteTime;
World world;
SearchGrid search;
Arena tileArena;
TileDatabase tileDatabase;
Arena plantArena;
PlantDatabase plantDatabase;
Arena regrowthPlantArena;
RegrowthPlantDatabase regrowthPlantDatabase;
Arena animalArena;
AnimalDatabase animalDatabase;
Arena unitArena;
UnitDatabase unitDatabase;
Arena itemArena;
ItemDatabase itemDatabase;
BuildableDatabase buildableDatabase;
Arena buildableArena;  

void initWorld();

void deinitWorld();

GameSave &saveGame(std::string name, GameSave *save);

void loadGame(GameSave& save);  

void newGame();

void quit();

void handleEvent(SDL_Event *e);

void processWorld();

void gameLoop();

uint16_t getDay();

};


	
