#pragma once
#include <extern/SDL_FontCache.h>
#include <SDL2/SDL_ttf.h>
#include <render/screen.hpp>
FC_Font* amble20 = FC_CreateFont();  
Uint8 fontErrorAmble20 = FC_LoadFont(amble20, renderer, "../../fonts/Amble-Regular.ttf", 20, FC_MakeColor(0,0,0,255), TTF_STYLE_NORMAL);

struct FontData
{
	
};	

//TODO: calculate these automatically once, print, then hardcode. 
struct RawFontData {
	int cagliostroSize = 4;
	int cantarellSize = 3;
};

// create font atlas for different screen sizes (or at least current screen size)
void createFontAtlas()
{
	
}	
