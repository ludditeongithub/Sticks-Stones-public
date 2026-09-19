#pragma once
#include "render/animation.hpp"
#include "render/sprite.hpp"
#include "ui/components/button_functionality.hpp"
#include "ui/components/drop_down_menu.hpp"
#include <cereal/details/helpers.hpp>
#include <SDL_FontCache.h>
#include <core/SDL_FontCache.h>
#include <render/screen.hpp>
#include <string>
#include <ui/components/text.hpp>
#include <ui/components/button.hpp>
#include <ui/components/drop_down_menu.hpp>
#include <fstream>
#include "fonts.hpp"
#include "system.hpp"

bool init_first_launch_window()
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
		window = SDL_CreateWindow("First Launch", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, first_launch_window_width, first_launch_window_height,SDL_WINDOW_SHOWN);
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

struct FirstLaunchBuffer
{
	bool first_launch = true;
	Coord user_screen_resolution;
	bool fullscreen = false;

	template <typename Archive> void serialize(Archive &a) { a(first_launch, 1); }
};

	void launch_first_launcher(FirstLaunchBuffer flb)
	{
fc_make_color(9, 9, 9, 255), TTF_STYLE_NORMAL);
		

		PositionedText fullscreen = {amble20, "Fullscreen: ", {30, 30}};
		int text_width = fc_get_width(amble20, fullscreen.text);
		CheckboxUI cb = CheckboxUI({text_width + 8,30}, {30,30}, SpriteSheet::button[ButtonSprite::Checkbox].unpressed, SpriteSheet::button[ButtonSprite::Checkbox].pressed);
		Text text = {amble20, "Click to Select Window Dimensions"};
		TextButtonUI header_button = TextButtonUI(text, NullBF(), ButtonSprite::FirstLaunchButton, {30, static_cast<int>(fullscreen.position.y) + 50});

		DropdownMenu ddm = DropdownMenu(header_button, screen_dimensions.size());

		int accum = header_button.top_left_corner.y + header_button.dimensions.y;
		for (auto sd : screen_dimensions)
		{		  
		  ddm.add_item(TextButtonUI({amble20, std::to_string(sd.x) + " x " + std::to_string(sd.y)},                                           ChangeScreenDimensionsBF(sd), ButtonSprite::FirstLaunchButton, {header_button.top_left_corner.x, accum}));
		}

                Text lbt = {amble20, "Launch"};
		TextButtonUI launch_button =
                  TextButtonUI(lbt, LaunchBF(Launches::GameWindow),				 ButtonSprite::FirstLaunchButton, {180, static_cast<int>(fullscreen.position.y + 150)});
		launch_button.render(main_screen_viewport);
                
	}


FirstLaunchBuffer handle_launch()
{
FirstLaunchBuffer flb;
std::string file = "first_launch.bin";
std::ifstream is(file);

try
{
    cereal::BinaryInputArchive first_launch_archive = cereal::BinaryInputArchive(is);
    flb.serialize(first_launch_archive);
}
catch (...)
{
  flb = FirstLaunchBuffer{};
  launch_first_launcher(flb);
}
 return flb;
}

void launch()
{
        FirstLaunchBuffer flb = handle_launch();	
	 (flb.user_screen_resolution.x, flb.user_screen_resolution.y, flb.fullscreen);
        
}
