#include "core/mouse.hpp"
#include "render/screen.hpp"
#include <SDL2/SDL_events.h>
#include <core/data.hpp>
#include <ui/components/button.hpp>
#include <render/sprite_sheet_settings.hpp>
#include <simulation/game.cpp>

//TODO: loadGameButton

struct MainMenu
{
	SCoord background = {};
	const int buttonLeftAlignment = SCREEN_WIDTH / 2 - (SpriteSheet::buttonSprites[static_cast<int>(Button::MainButton)].dimensions.x / 2);
	SCoord newLeftCorner = {buttonLeftAlignment, 2 * SCREEN_HEIGHT / 6};
	SCoord loadLeftCorner = {buttonLeftAlignment / 2, 3 * SCREEN_HEIGHT / 6};
	SCoord optionsLeftCorner = {buttonLeftAlignment / 2, 4 * SCREEN_HEIGHT / 6};
	SCoord aboutLeftCorner = {buttonLeftAlignment / 2, 5 * SCREEN_HEIGHT / 6};
	SCoord Unpressed = SpriteSheet::buttonSprites[static_cast<int>(Button::MainButton)].position;
	SCoord Hover = SpriteSheet::buttonSprites[static_cast<int>(Button::MainButtonHover)].position;
	SCoord Pressed = SpriteSheet::buttonSprites[static_cast<int>(Button::MainButtonPressed)].position;
	SCoord buttonDimensions = SpriteSheet::buttonSprites[static_cast<int>(Button::MainButton)].dimensions;
	ButtonUI newGameButton = ButtonUI(newLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
	ButtonUI loadGameButton = ButtonUI(loadLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
	ButtonUI aboutButton = ButtonUI(aboutLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
	ButtonUI optionsButton =
	    ButtonUI(optionsLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);

	SCoord videoLeftCorner = {buttonLeftAlignment, 2 * SCREEN_HEIGHT / 6};
	SCoord audioLeftCorner = {buttonLeftAlignment / 2, 3 * SCREEN_HEIGHT / 6};
	SCoord keybindingsLeftCorner = {buttonLeftAlignment / 2, 4 * SCREEN_HEIGHT / 6};

	ButtonUI videoButton =
	    ButtonUI(videoLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
	ButtonUI audioButton =
	    ButtonUI(audioLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);
	ButtonUI keybindingsButton =
	    ButtonUI(keybindingsLeftCorner, buttonDimensions, Unpressed, Hover, Pressed);

	enum class Mode
	{
		Main,
		Options,
		Load,
		Video,
		Audio		
	};
	Mode mode;

	void render() {}	
	
	void handleEvent(SDL_Event *e)
	{
		SCoord mousePosition;
		SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
		switch (mode)
		{
		case Mode::Main:
			mainHandle(e, mousePosition);
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

	void optionsHandle(SDL_Event *e, SCoord mousePosition)
	{
		if (e->type == SDL_MOUSEBUTTONUP) {
			if (mouseInside(mousePosition, audioLeftCorner, buttonDimensions)) mode = Mode::Audio;
			else if (mouseInside(mousePosition, videoLeftCorner, buttonDimensions)) mode = Mode::Video;
		}
	}
	void audioHandle(SDL_Event *e, SCoord mousePosition) {}
	void videoHandle(SDL_Event *e, SCoord mousePosition) {} 
}	
