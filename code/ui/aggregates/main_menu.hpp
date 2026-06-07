#pragma once
#include "core/mouse.hpp"
#include "render/screen.hpp"
#include "ui/system.hpp"
#include <SDL2/SDL_events.h>
#include <core/data.hpp>
#include <ui/components/button.hpp>
#include <render/sprite_sheet_settings.hpp>
#include <simulation/launch_game.hpp>

//TODO: loadGameButton

struct MainMenu
{
	uint16_t userScreenWidth;
	uint16_t userScreenHeight;
	uint8_t rawToUserScalar;
	// Button Positions
	SCoord background = {}; //TODO
	int buttonLeftAlignment = SCREEN_WIDTH / 2 - (SpriteSheet::buttonSprites[static_cast<int>(Button::MainButton)].w / 2);
	
	SCoord newLeftCorner = {buttonLeftAlignment, 2 * SCREEN_HEIGHT / 6};
	SCoord loadLeftCorner = {buttonLeftAlignment / 2, 3 * SCREEN_HEIGHT / 6};
	SCoord optionsLeftCorner = {buttonLeftAlignment / 2, 4 * SCREEN_HEIGHT / 6};
	SCoord aboutLeftCorner = {buttonLeftAlignment / 2, 5 * SCREEN_HEIGHT / 6};
	// Button Sprite Sheet positions
	SCoord Unpressed = {SpriteSheet::buttonSprites[static_cast<int>(Button::MainButton)].x, SpriteSheet::buttonSprites[static_cast<int>(Button::MainButton)].y};
	SCoord Hover = {SpriteSheet::buttonSprites[static_cast<int>(Button::MainButtonHover)].x, SpriteSheet::buttonSprites[static_cast<int>(Button::MainButtonHover)].y};
	SCoord Pressed = {SpriteSheet::buttonSprites[static_cast<int>(Button::MainButtonPressed)].x, SpriteSheet::buttonSprites[static_cast<int>(Button::MainButtonPressed)].y};
	SCoord buttonDimensions = {SpriteSheet::buttonSprites[static_cast<int>(Button::MainButton)].x, SpriteSheet::buttonSprites[static_cast<int>(Button::MainButton)].y};
	
	ButtonUI newGameButton;
	ButtonUI loadGameButton;
	ButtonUI aboutButton;
	ButtonUI optionsButton;
	
	SCoord videoLeftCorner;	
	SCoord audioLeftCorner;
	SCoord keybindingsLeftCorner;

	ButtonUI videoButton;
	ButtonUI audioButton;
	ButtonUI keybindingsButton;
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
		newGameButton = ButtonUI(newLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
		loadGameButton = ButtonUI(loadLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
		aboutButton = ButtonUI(aboutLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
		optionsButton =
		    ButtonUI(optionsLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);

		videoLeftCorner = {buttonLeftAlignment, 2 * SCREEN_HEIGHT / 6};
		audioLeftCorner = {buttonLeftAlignment / 2, 3 * SCREEN_HEIGHT / 6};
		keybindingsLeftCorner = {buttonLeftAlignment / 2, 4 * SCREEN_HEIGHT / 6};

	 videoButton = ButtonUI(videoLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
	 audioButton = ButtonUI(audioLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
	 keybindingsButton = ButtonUI(keybindingsLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
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
