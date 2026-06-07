#pragma once
#include "ui/aggregates/main_menu.hpp"
#include "ui/system.hpp"
#include <core/data.hpp>
#include <cstdint>
#include <core/saves.hpp>

class ButtonFunctionality
{
	public:
	virtual void trigger();
};

class NullBF : public ButtonFunctionality
{
private:
public:
	void trigger() override {};
};

class ChangeScreenDimensionsBF : public ButtonFunctionality
{
	public:
	  Coord screenDimensions;
	ChangeScreenDimensionsBF(Coord screenDimensions) : screenDimensions(screenDimensions) {}
	void trigger() override
	{
	  currentScreenDimensions = screenDimensions;
	}
};

enum class Launches : uint8_t
{
	GameWindow,
	NewGame
};

class LaunchBF : ButtonFunctionality
{
public:
  LaunchBF(Launches launches) : launches(launches) {};
  Launches launches;
  void trigger() override
  {
    
  }
};

class LoadGameBF : ButtonFunctionality
{
private:
public:
  LoadGameBF(GameSave &save) {};
  void trigger() override
  {
    
  }	  
};

class SaveGameBF : ButtonFunctionality
{
private:
public:
  SaveGameBF (GameSave& save) {};
  void trigger() override
  {
  }	  
};




