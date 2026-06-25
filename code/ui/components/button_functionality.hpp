#pragma once
#include "simulation/launch_game.hpp"
#include "ui/aggregates/main_menu.hpp"
#include "ui/system.hpp"
#include <core/data.hpp>
#include <cstdint>
#include <core/saves.hpp>
#include "pop-up_box.hpp"

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
	  screenDimensions = screenDimensions;
	}
};

enum class Launches : uint8_t
{
	GameWindow,
	NewGame
};

class LaunchBF : public ButtonFunctionality
{
public:
  LaunchBF(Launches launches) : launches(launches) {};
  Launches launches;
  void trigger() override
  {
    
  }
};

// MAIN MENU
struct NewGameBF : public ButtonFunctionality
{
      private:
  MainMenu& main;
      public:
	NewGameBF(MainMenu &main) : main(main) {}

	void trigger() override
	{
		g_Game = new Game();
		// TODO: player can adjust world gen settings
                g_Game->initNewWorld();
		g_Game->newGame();
        }
};

struct ContinueBF : public ButtonFunctionality {
      public:
	ContinueBF()
	{
          // get most recent game save from binary          
        }
};

struct LoadMenuBF : public ButtonFunctionality {
     private:
  MainMenu& main;
      public:
	LoadMenuBF(MainMenu &main) : main(main) {}

	void trigger() override
	{
          
        }
};

class LoadGameBF : public ButtonFunctionality
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

class AboutBF : public ButtonFunctionality
{
private:
public:
  AboutBF() {};
};

class OptionsBF : public ButtonFunctionality
{
private:
public:
  OptionsBF() {};
};

class VideoBF : public ButtonFunctionality
{
private:
public:
  VideoBF() {};
  
};

class AudioBF : public ButtonFunctionality
{
private:
public:
  AudioBF() {};
};

class KeybindingsBF : public ButtonFunctionality
{
private:
public:
  KeybindingsBF() {};  
};

// IN GAME










