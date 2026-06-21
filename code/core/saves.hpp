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
  std::time_t lastSaved;  
  GameSave(std::string name) : name(name)
  {	  
    std::chrono::time_point<std::chrono::system_clock> now =std::chrono::system_clock::now();
    lastSaved = std::chrono::system_clock::to_time_t(now);
  };

  void save(Game& game)
  {    
    std::ofstream ofs(name, std::ios::binary);
    cereal::BinaryOutputArchive archive(ofs);
    // NOTE: the order of this is VERY important!
    game.tileDatabase.save();
    game.plantDatabase.save();
    game.animalDatabase.save();
    game.unitDatabase.save();
    game.itemDatabase.save();
    game.buildableDatabase.save();
  }

  void load(Game& game)
  {    
    std::ifstream ifs(name, std::ios::binary);
    cereal::BinaryInputArchive archive(ifs);
    // NOTE: the order of this is VERY important!
    game.tileDatabase.load(game.tileArena, archive);
    game.plantDatabase.load(game.plantArena, archive);
    game.animalDatabase.load(game.animalArena, archive);
    game.unitDatabase.load(game.unitArena, archive);
    game.itemDatabase.load(game.itemArena, archive);
    game.buildableDatabase.load(game.buildableArena, archive);
  }

  bool confirmSave()
  {
    
  }
};

std::vector<GameSave> saves;
