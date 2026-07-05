#pragma once
#include <extern/SDL_FontCache.h>
#include <SDL2/SDL_ttf.h>
#include <render/screen.hpp>
struct FontData
{
	
};	

//TODO: calculate these automatically once, print, then hardcode. 
struct RawFontData {
	int cagliostroSize = 4;
	int cantarellSize = 3;
};

// create font atlas for different screen sizes (or at least current screen size)
void createFontAtlas(Coord screenSize)
{
	
}	
