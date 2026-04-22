#include "core/mouse.hpp"
#include <SDL2/SDL_events.h>
#include <core/data.hpp>
#include <ui/components/button.hpp>
#include <render/sprite_sheet_settings.hpp>

//TODO: loadGameButton

struct MainMenu {
	SCoord newLeftCorner;
	SCoord continueLeftCorner;
	SCoord optionsLeftCorner;
	SCoord aboutLeftCorner;
	ButtonUI newGame;
	ButtonUI continueGame;
	ButtonUI about;
	ButtonUI options;
	SCoord buttonDimensions;
	
	MainMenu(SCoord screenDimensions)
	{
		newLeftCorner = {screenDimensions.x / 2, screenDimensions.y / 6};
		continueLeftCorner = {screenDimensions.x / 2, screenDimensions.y / 5};
		optionsLeftCorner = {screenDimensions.x / 2, screenDimensions.y / 4};
		aboutLeftCorner = {screenDimensions.x / 2, screenDimensions.y / 3};
		
		buttonDimensions = {screenDimensions.x / 8, screenDimensions.y / 7};
		
	newGame = ButtonUI(newLeftCorner, buttonDimensions, SpriteSheet::MainButtonUnpressed, SpriteSheet::MainButtonHover, SpriteSheet::MainButtonPressed);
	continueGame = ButtonUI(continueLeftCorner, buttonDimensions, SpriteSheet::MainButtonUnpressed, SpriteSheet::MainButtonHover, SpriteSheet::MainButtonPressed);
	options = ButtonUI(optionsLeftCorner, buttonDimensions, SpriteSheet::MainButtonUnpressed, SpriteSheet::MainButtonHover, SpriteSheet::MainButtonPressed);
	about = ButtonUI(aboutLeftCorner, buttonDimensions, SpriteSheet::MainButtonUnpressed, SpriteSheet::MainButtonHover, SpriteSheet::MainButtonPressed);
	}

	void handleEvent(SDL_Event *e)
	{
		SCoord mousePosition;
		SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
		if (e->type == SDL_MOUSEBUTTONUP) {
		if (mouseInside(mousePosition, newLeftCorner, buttonDimensions)) newGame();
		else if (mouseInside(mousePosition, continueLeftCorner, buttonDimensions)) continueGame();
		else if (mouseInside(mousePosition, optionsLeftCorner, buttonDimensions)) options();
		else if (mouseInside(mousePosition, aboutLeftCorner, buttonDimensions)) about();
		}
	}		
}

