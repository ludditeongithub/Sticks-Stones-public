#pragma once
#include "core/mouse.hpp"
#include "render/screen.hpp"
#include "ui/system.hpp"
#include <SDL2/SDL_events.h>
#include <core/data.hpp>
#include <ui/components/button.hpp>
#include <render/sprite_sheet_settings.hpp>
#include <simulation/launch_game.hpp>

// TODO: loadGameButton

struct MainButtonUI : public ButtonUI {
  MainButtonUI(const ButtonFunctionality function, const SCoord leftCorner) : ButtonUI(function, ButtonSprite::MainButton, leftCorner)
	{
          
        }
};

struct MainMenu
{
	uint16_t userScreenWidth;
	uint16_t userScreenHeight;
	uint8_t rawToUserScalar;
	// Button Positions
	SCoord background = {}; //TODO
	int buttonLeftAlignment =
	    SCREEN_WIDTH / 2 -
	    (SpriteSheet::buttonSprites[static_cast<int>(ButtonSprite::MainButton)].w / 2);
	
	SCoord newLeftCorner = {buttonLeftAlignment, 2 * SCREEN_HEIGHT / 6};
	SCoord loadLeftCorner = {buttonLeftAlignment / 2, 3 * SCREEN_HEIGHT / 6};
	SCoord optionsLeftCorner = {buttonLeftAlignment / 2, 4 * SCREEN_HEIGHT / 6};
	SCoord aboutLeftCorner = {buttonLeftAlignment / 2, 5 * SCREEN_HEIGHT / 6};
	MainButtonUI newGameButton;
	MainButtonUI loadGameButton;
	MainButtonUI aboutButton;
	MainButtonUI optionsButton;
	
	SCoord videoLeftCorner;	
	SCoord audioLeftCorner;
	SCoord keybindingsLeftCorner;

	MainButtonUI videoButton;
	MainButtonUI audioButton;
	MainButtonUI keybindingsButton;
	SDL_Rect mainMenuViewport;

	enum class Mode
	{
		Main,
		Options,
		Load,
		Video,
		Audio
	};
	
	Mode mode;

	MainMenu() 
	{		
          newGameButton = MainButtonUI(NewGameBF(this), newLeftCorner);
          loadGameButton = MainButtonUI(LoadMenuBF(), loadLeftCorner);
          aboutButton = MainButtonUI(AboutBF(), aboutLeftCorner);
          optionsButton = MainButtonUI(OptionsBF(), optionsLeftCorner);

          videoLeftCorner = {buttonLeftAlignment, 2 * SCREEN_HEIGHT / 6};
          audioLeftCorner = {buttonLeftAlignment / 2, 3 * SCREEN_HEIGHT / 6};
          keybindingsLeftCorner = {buttonLeftAlignment / 2, 4 * SCREEN_HEIGHT / 6};

          videoButton = ButtonUI(VideoBF(), videoLeftCorner);
          audioButton = ButtonUI(AudioBF(), audioLeftCorner);
          keybindingsButton = ButtonUI(KeybindingsBF(),keybindingsLeftCorner);
	}

	void render()
	{
        newGameButton.render();
	loadGameButton.render();
	aboutButton.render();
	optionsButton.render();
	videoButton.render();
	audioButton.render();
	keybindingsButton.render();
	}	
	
	void handleEvent(SDL_Event *e)
	{
		SCoord mousePosition;
		SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
		switch (mode)
		{
		case Mode::Main:
			mainHandle(e, mousePosition);
			break;
		case Mode::Load:
			loadHandle(e, mousePosition);
			break;
		case Mode::Options:
			optionsHandle(e, mousePosition);
			break;
		case Mode::Video:
			videoHandle(e, mousePosition);
			break;
		case Mode::Audio:
			audioHandle(e, mousePosition);
			break;
		}
	}

	void mainHandle(SDL_Event *e, SCoord mousePosition)
	{
		
	}

	void loadHandle(SDL_Event *e, SCoord mousePosition)
	{
		//TODO: finish UI element ScrollableList. saves are ScrollableList.
		if (e->type == SDL_MOUSEBUTTONUP) {
			if (mouseInside(mousePosition, newLeftCorner, buttonDimensions)) {
				startGame();
			}
			else if (mouseInside(mousePosition, loadLeftCorner, buttonDimensions))
			{
				mode = Mode::Load;
			} else if (mouseInside(mousePosition, optionsLeftCorner, buttonDimensions)) mode = Mode::Options;
		}
	}		

	void optionsHandle(SDL_Event *e, SCoord mousePosition)
	{
		if (e->type == SDL_MOUSEBUTTONUP) {
			if (mouseInside(mousePosition, audioLeftCorner, buttonDimensions)) mode = Mode::Audio;
			else if (mouseInside(mousePosition, videoLeftCorner, buttonDimensions)) mode = Mode::Video;
		}
	}
	void audioHandle(SDL_Event *e, SCoord mousePosition);
	void videoHandle(SDL_Event *e, SCoord mousePosition);
};	
