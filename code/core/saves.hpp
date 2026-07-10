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
    game.tileDatabase.save(archive);
    game.plantDatabase.save(archive);
    game.animalDatabase.save(archive);
    game.playerUnitDatabase.save(archive);
	game.NPCUnitDatabase.save(archive);
    game.itemDatabase.save(archive);
    game.buildableDatabase.save(archive);
  }

  void load(Game& game)
  {    
    std::ifstream ifs(name, std::ios::binary);
    cereal::BinaryInputArchive archive(ifs);
    // NOTE: the order of this is VERY important!
    game.tileDatabase.load(archive);
    game.plantDatabase.load(archive);
    game.animalDatabase.load(archive);
    game.playerUnitDatabase.load(archive);
	game.NPCUnitDatabase.load(archive);
    game.itemDatabase.load(archive);
    game.buildableDatabase.load(archive);
  }

  bool confirm_save()
  {
    
  }
};

std::vector<GameSave> saves;
