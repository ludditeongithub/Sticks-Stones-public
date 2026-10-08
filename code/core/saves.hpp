#pragma once
#include <chrono>
#include <fstream>
#include <logic/simulation/game.hpp>
#include <cereal/archives/binary.hpp>

struct GameSave
{
private:
public:
  std::string name;
  std::time_t last_saved;  
  GameSave(std::string name) : name(name)
  {	  
    std::chrono::time_point<std::chrono::system_clock> now =std::chrono::system_clock::now();
    last_saved = std::chrono::system_clock::to_time_t(now);
  };

  void serialize(Game& game)
  {    
    std::ofstream ofs(name, std::ios::binary);
    cereal::BinaryOutputArchive archive(ofs);
    // NOTE: the order of this is VERY important!
    game.tile_database.serialize(archive);
    game.plant_database.serialize(archive);
    game.animal_database.serialize(archive);
    game.unit_database.serialize(archive);
    game.item_database.serialize(archive);
    game.buildable_database.serialize(archive);
  }

  void load_and_init_memory(Game& game)
  {    
    std::ofstream ofs(name, std::ios::binary);
    cereal::BinaryOutputArchive archive(ofs);
    size_t arena_capacity;
    archive(arena_capacity);
    game.arena = Arena(arena_capacity);
    game.init_databases();
    serialize(game);
  }

  bool confirm_serialize()
  {
    
  }
};

std::vector<GameSave> saves;
