#pragma once
#include <chrono>

class GameSave
{
private:
public:
  std::string name;
  std::time_t lastSaved;  
  GameSave(std::string name) : name(name)
  {	  
    std::chrono::time_point<std::chrono::system_clock> now =std::chrono::system_clock::now();
    std::time_t lastSaved = std::chrono::system_clock::to_time_t(now);
    save();
  };

  void save(Game& game)
  {
    // NOTE: the order of this is VERY important!
    
  }
};
