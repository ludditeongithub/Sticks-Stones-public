#pragma once
#include <core/coord.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_hints.h>
#include <SDL_error.h>
#include <SDL_rect.h>
#include <SDL_stdinc.h>
#include <stdio.h>
#include <string>
#include <cstdint>
#include <cassert>
#include <algorithm>
#include "display/render/texture.hpp"
#include <data/run/camera.hpp>
#include <data/game/screen.hpp>

struct WindowSystem
{
      private:
	inline static WindowSystem *instance = nullptr;

      public:        
	SDL_Rect whole_display_viewport;
	
	uint16_t user_screen_width;
	uint16_t user_screen_height;
	
	uint8_t raw_to_user_scalar;
	bool fullscreen;
	enum class BlackBarStatus
	{
		None,
		Horizontal,
		Vertical,
		Both
	};
	BlackBarStatus black_bars;
	Coord black_bar_size; //of single side

	WindowSystem(uint16_t user_screen_width, uint16_t user_screen_height, bool fullscreen) : user_screen_width(user_screen_width), user_screen_height(user_screen_height), fullscreen(fullscreen)
	{
          instance = this;
		  set_display_settings(user_screen_width, user_screen_height);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); //use nearest-neighbor
	}

	static WindowSystem &get_instance()
	{
		assert(instance != nullptr);
		return *instance;
        }

//TODO: check if manually adjusting display viewport is necessary with SDL's scaling	
	void set_display_settings(uint16_t user_screen_width, uint16_t user_screen_height)
	{
		this->user_screen_width = user_screen_width;
		this->user_screen_height = user_screen_height;
		float width_ratio = (float)((float)user_screen_width / (float)SCREEN_WIDTH);
		float height_ratio = (float)((float)user_screen_height / (float)SCREEN_HEIGHT);
		uint16_t actual_width_ratio = (uint16_t)width_ratio;
		uint16_t actual_height_ratio = (uint16_t)height_ratio;
		raw_to_user_scalar =
		    static_cast<uint16_t>(std::min(actual_width_ratio, actual_height_ratio));
		SDL_SetWindowSize(window, user_screen_width, user_screen_height);
		SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
		
		if (fullscreen) {
                // calculate black bars
		if (actual_height_ratio < actual_width_ratio)
		{
			black_bars = BlackBarStatus::Horizontal;
			black_bar_size = {
			    user_screen_width,
			    uint32_t(user_screen_height - (SCREEN_HEIGHT * actual_height_ratio))};
			whole_display_viewport = {0, (int)black_bar_size.y / 2, SCREEN_WIDTH * actual_width_ratio, SCREEN_HEIGHT * actual_height_ratio};
		} else if (actual_width_ratio > actual_height_ratio) {
			black_bars = BlackBarStatus::Vertical;
			black_bar_size = {
			    uint32_t(user_screen_width - (SCREEN_WIDTH * actual_width_ratio)),
			    user_screen_height};
			whole_display_viewport = {(int)black_bar_size.x / 2, 0, SCREEN_WIDTH * actual_width_ratio, SCREEN_HEIGHT * actual_height_ratio};
		}
		else if (actual_height_ratio * SCREEN_HEIGHT != user_screen_height && actual_width_ratio * SCREEN_WIDTH != user_screen_width)
		{
			black_bars = BlackBarStatus::Both;
			black_bar_size = {
			    uint32_t(user_screen_width - (SCREEN_WIDTH * actual_width_ratio)), uint32_t(user_screen_height - (SCREEN_HEIGHT * actual_height_ratio))};
			whole_display_viewport = {(int)black_bar_size.x / 2, (int)black_bar_size.y / 2, SCREEN_WIDTH * actual_width_ratio, SCREEN_HEIGHT * actual_height_ratio};
		}
		else {
			black_bars = BlackBarStatus::None;
		}
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); //TODO: may be SDL_WINDOW_FULLSCREEN_DESKTOP
		}
		else
		{
			whole_display_viewport = {0,0, user_screen_width, user_screen_height};
		}
	}		

	//TODO: initializable as fullscreen
	bool init_window()
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
					   SDL_WINDOWPOS_UNDEFINED, user_screen_width, user_screen_height,
					   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
			whole_display_viewport = {0, 0, user_screen_width, user_screen_height};

			// create raw rendering
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			
		}
	}
	return success;
}

bool load_sprite_sheet()
{
	// Loading success flag
	bool success = true;
	std::string path = "sprite_sheet.png";
	// Load sprite sheet texture
	if (!sprite_sheet_texture.load_from_file(path))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	return success;
}	

void close_window()
{
	sprite_sheet_texture.free();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	SDL_Quit();
}
};

extern WindowSystem g_window_system;
