#pragma once
#include "render/sprite.hpp"
#include "render/sprite_sheet_settings.hpp"
#include "ui/components/drop_down_menu.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <render/screen.hpp>
#include <string>
#include <ui/components/button.hpp>
#include <ui/components/drop_down_menu.hpp>

	bool initFirstLaunchWindow()
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
		window = SDL_CreateWindow("First Launch", SDL_WINDOWPOS_UNDEFINED,
					   SDL_WINDOWPOS_UNDEFINED, FIRST_LAUNCH_WINDOW_WIDTH, FIRST_LAUNCH_WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
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

			// create raw rendering
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			
		}
	}
	return success;
	}

	void displayFirstLaunch()
	{
		ButtonSpriteData bsd = SpriteSheet::buttonSprites[FirstLaunchButton];

		TextButtonUI headerButton = TextButtonUI("Select Screen Dimensions", {30, 30}, {20, 180}, bsd.dimensions, bsd.unpressed, bsd.hover, bsd.pressed);
		DropdownMenu ddm = DropdownMenu(headerButton, screen_dimensions.size());
		for (auto y: screen_dimensions) {
			ddm.addItem(TextButtonUI(std::to_string(screen_dimensions.x) + " x " + std::to_string(screen_dimensions.y)));
		}
	}		
