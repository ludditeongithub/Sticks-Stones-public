#pragma once
#include <SDL_FontCache.h>
#include <SDL2/SDL_ttf.h>
#include <render/screen.hpp>
#include "colors.hpp"

// @codegen:begin fonts


  FC_Font* cagliostro_4;  
  FC_Font* cantarell_3;  
  FC_Font* amble_3;  

void init_fonts() {
  fc_load_font_from_ttf(cagliostro_4, renderer, TTF_OpenFont("../../fonts/Cagliostro-Regular.ttf", 4), black);
  fc_load_font_from_ttf(cantarell_3, renderer, TTF_OpenFont("../../fonts/Cantarell-Regular.ttf", 3), black);
  fc_load_font_from_ttf(amble_3, renderer, TTF_OpenFont("../../fonts/Amble-Regular.ttf", 3), black);
}
// @codegen:end fonts

// create font atlas for different screen sizes (or at least current screen size)
void create_font_atlas(Coord screen_size)
{
	
}

