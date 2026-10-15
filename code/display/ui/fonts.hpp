#pragma once
#include <../extern/SDL_FontCache.h>
#include <SDL2/SDL_ttf.h>
#include <display/render/screen.hpp>
#include "colors.hpp"

// @codegen:begin fonts


  FC_Font* cagliostro;  
  FC_Font* cantarell;  
  FC_Font* amble;

void init_fonts(float scale) {
  fc_load_font_from_ttf(cagliostro, renderer, TTF_OpenFont("assets/fonts/Cagliostro-Regular.ttf", 8 * scale), BLACK);
  fc_load_font_from_ttf(cantarell, renderer, TTF_OpenFont("assets/fonts/Cantarell-Regular.ttf", 8 * scale), BLACK);
  fc_load_font_from_ttf(amble, renderer, TTF_OpenFont("assets/fonts/Amble-Regular.ttf", 8 * scale), BLACK);
}
// @codegen:end fonts

