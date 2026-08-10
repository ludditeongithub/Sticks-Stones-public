#pragma once
#include <chrono>
#include <fstream>
#include <simulation/game.hpp>
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

  void save(Game& game)
  {    
    std::ofstream ofs(name, std::ios::binary);
    cereal::BinaryOutputArchive archive(ofs);
    // NOTE: the order of this is VERY important!
    game.tile_database.save(archive);
    game.plant_database.save(archive);
    game.animal_database.save(archive);
    game.player_unit_database.save(archive);
    game.NPC_unit_database.save(archive);
    game.item_database.save(archive);
    game.buildable_database.save(archive);
  }

  void load(Game& game)
  {    
    std::ifstream ifs(name, std::ios::binary);
    cereal::BinaryInputArchive archive(ifs);
    // NOTE: the order of this is VERY important!
    game.tile_database.load(archive);
    game.plant_database.load(archive);
    game.animal_database.load(archive);
    game.player_unit_database.load(archive);
    game.NPC_unit_database.load(archive);
    game.item_database.load(archive);
    game.buildable_database.load(archive);
  }

  bool confirm_save()
  {
    
  }
};

std::vector<GameSave> saves;
