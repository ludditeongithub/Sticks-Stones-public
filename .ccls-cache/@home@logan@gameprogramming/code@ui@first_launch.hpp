#pragma once
#include "render/animation.hpp"
#include "render/sprite.hpp"
#include "render/sprite_sheet_settings.hpp"
#include "ui/components/button_functionality.hpp"
#include "ui/components/drop_down_menu.hpp"
#include <cereal/details/helpers.hpp>
#include <extern/SDL_FontCache.h>
#include <core/SDL_FontCache.h>
#include <render/screen.hpp>
#include <string>
#include <ui/components/text.hpp>
#include <ui/components/button.hpp>
#include <ui/components/drop_down_menu.hpp>
#include <fstream>
#include "fonts.hpp"
#include "system.hpp"

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
		window = SDL_CreateWindow("First Launch", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, FIRST_LAUNCH_WINDOW_WIDTH, FIRST_LAUNCH_WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
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
	bool firstLaunch = true;
	Coord userScreenResolution;
	bool fullscreen = false;

	template <typename Archive> void serialize(Archive &a) { a(firstLaunch, 1); }
};

	void launchFirstLauncher(FirstLaunchBuffer flb)
	{
	        FC_Font* amble20 = FC_CreateFont();
		FC_LoadFont(amble20, renderer, "../../fonts/Amble-Regular.ttf", 20,
			    FC_MakeColor(9, 9, 9, 255), TTF_STYLE_NORMAL);
		

		PositionedText fullscreen = {amble20, "Fullscreen: ", {30, 30}};
		int textWidth = FC_GetWidth(amble20, fullscreen.text);
		CheckboxUI cb = CheckboxUI({textWidth + 8,30}, {30,30}, SpriteSheet::buttonSprites[ButtonSprite::Checkbox].unpressed, SpriteSheet::buttonSprites[ButtonSprite::Checkbox].pressed);
		Text text = {amble20, "Click to Select Window Dimensions"};
		TextButtonUI headerButton = TextButtonUI(text, NullBF(), ButtonSprite::FirstLaunchButton, {30, static_cast<int>(fullscreen.position.y) + 50});

		DropdownMenu ddm = DropdownMenu(headerButton, screen_dimensions.size());

		int accum = headerButton.topLeftCorner.y + headerButton.dimensions.y;
		for (auto sd : screen_dimensions)
		{		  
		  ddm.addItem(TextButtonUI({amble20, std::to_string(sd.x) + " x " + std::to_string(sd.y)},                                           ChangeScreenDimensionsBF(sd), ButtonSprite::FirstLaunchButton, {headerButton.topLeftCorner.x, accum}));
		}

                Text lbt = {amble20, "Launch"};
		TextButtonUI launchButton =
                  TextButtonUI(lbt, LaunchBF(Launches::GameWindow),				 ButtonSprite::FirstLaunchButton, {180, static_cast<int>(fullscreen.position.y + 150)});
		launchButton.render(mainScreenViewport);
                
	}


FirstLaunchBuffer handleLaunch()
{
FirstLaunchBuffer flb;
std::string file = "first_launch.bin";
std::ifstream is(file);

try
{
    cereal::BinaryInputArchive firstLaunchArchive = cereal::BinaryInputArchive(is);
    flb.serialize(firstLaunchArchive);
}
catch (...)
{
  flb = FirstLaunchBuffer{};
  launchFirstLauncher(flb);
}
 return flb;
}

void launch()
{
        FirstLaunchBuffer flb = handleLaunch();	
	g_UISystem = new UISystem(flb.userScreenResolution.x, flb.userScreenResolution.y, flb.fullscreen);
        
}
