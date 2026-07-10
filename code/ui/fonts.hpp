#pragma once
#include <extern/SDL_FontCache.h>
#include <SDL2/SDL_ttf.h>
#include <render/screen.hpp>
struct FontData
{
	
};	

//TODO: calculate these automatically once, print, then hardcode. 
struct RawFontData {
	int cagliostro_size = 4;
	int cantarell_size = 3;
};

// create font atlas for different screen sizes (or at least current screen size)
void create_font_atlas(Coord screen_size)
{
	
}	
