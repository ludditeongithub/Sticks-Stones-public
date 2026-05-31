#pragma once
#include "render/screen.hpp"
#include <SDL2/SDL_render.h>
#include <ui/aggregates/main_menu.hpp>
#include <cstdint>
#include <SDL2/SDL_video.h>

struct UISystem
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Rect wholeDisplayViewport;
	
	uint16_t userScreenWidth;
	uint16_t userScreenHeight;
	
	uint8_t rawToUserScalar;
	bool fullscreen;
	enum class BlackBarStatus
	{
		None,
		Horizontal,
		Vertical,
		Both
	};
	BlackBarStatus blackBars;
	Coord blackBarSize; //of single side
	MainMenu* mainMenu;

	UISystem(uint16_t userScreenWidth, uint16_t userScreenHeight, bool fullscreen) : userScreenWidth(userScreenWidth), userScreenHeight(userScreenHeight)
	{
		initWindow();
		setDisplaySettings(userScreenWidth, userScreenHeight);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); //use nearest-neighbor
		mainMenu = new MainMenu();
	}

//TODO: check if manually adjusting display viewport is necessary with SDL's scaling	
	void setDisplaySettings(uint16_t userScreenWidth, uint16_t userScreenHeight)
	{
		this->userScreenWidth = userScreenWidth;
		this->userScreenHeight = userScreenHeight;
		float widthRatio = (float)((float)userScreenWidth / (float)SCREEN_WIDTH);
		float heightRatio = (float)((float)userScreenHeight / (float)SCREEN_HEIGHT);
		uint16_t actualWidthRatio = (uint16_t)widthRatio;
		uint16_t actualHeightRatio = (uint16_t)heightRatio;
		rawToUserScalar =
		    static_cast<uint16_t>(std::min(actualWidthRatio, actualHeightRatio));
		SDL_SetWindowSize(window, userScreenWidth, userScreenHeight);
		SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
		
		if (fullscreen) {
                // calculate black bars
		if (actualHeightRatio < actualWidthRatio)
		{
			blackBars = BlackBarStatus::Horizontal;
			blackBarSize = {
			    userScreenWidth,
			    uint32_t(userScreenHeight - (SCREEN_HEIGHT * actualHeightRatio))};
			wholeDisplayViewport = {0, (int)blackBarSize.y / 2, SCREEN_WIDTH * actualWidthRatio, SCREEN_HEIGHT * actualHeightRatio};
		} else if (actualWidthRatio > actualHeightRatio) {
			blackBars = BlackBarStatus::Vertical;
			blackBarSize = {
			    uint32_t(userScreenWidth - (SCREEN_WIDTH * actualWidthRatio)),
			    userScreenHeight};
			wholeDisplayViewport = {(int)blackBarSize.x / 2, 0, SCREEN_WIDTH * actualWidthRatio, SCREEN_HEIGHT * actualHeightRatio};
		}
		else if (actualHeightRatio * SCREEN_HEIGHT != userScreenHeight && actualWidthRatio * SCREEN_WIDTH != userScreenWidth)
		{
			blackBars = BlackBarStatus::Both;
			blackBarSize = {
			    uint32_t(userScreenWidth - (SCREEN_WIDTH * actualWidthRatio)),
			    uint32_t(userScreenHeight - (SCREEN_HEIGHT * actualHeightRatio))};
			wholeDisplayViewport = {(int)blackBarSize.x / 2, (int)blackBarSize.y / 2, SCREEN_WIDTH * actualWidthRatio, SCREEN_HEIGHT * actualHeightRatio};
		}
		else {
			blackBars = BlackBarStatus::None;
		}
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); //TODO: may be SDL_WINDOW_FULLSCREEN_DESKTOP
		}
		else
		{
			wholeDisplayViewport = {0,0, userScreenWidth, userScreenHeight};
		}
	}		

	//TODO: initializable as fullscreen
	bool initWindow()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		window = SDL_CreateWindow("Sticks and Stones", SDL_WINDOWPOS_UNDEFINED,
					   SDL_WINDOWPOS_UNDEFINED, userScreenWidth, userScreenHeight,
					   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n",
				       SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}

			// create viewport
			wholeDisplayViewport = {0, 0, userScreenWidth, userScreenHeight};

			// create raw rendering
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			
		}
	}
	return success;
}

bool loadSpriteSheet()
{
	// Loading success flag
	bool success = true;
	std::string path = "sprite_sheet.png";
	// Load sprite sheet texture
	if (!spriteSheetTexture.loadFromFile(path))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
}	

void closeWindow()
{
	// Free loaded images
	spriteSheetTexture.free();

	// Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}
};

UISystem* UISystem;
