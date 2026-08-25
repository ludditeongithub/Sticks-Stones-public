#pragma once
#include <../extern/SDL_FontCache.h>
#include <SDL2/SDL_ttf.h>
#include <render/screen.hpp>
#include "colors.hpp"

// @codegen:begin fonts
  FC_Font* cagliostro;  
  FC_Font* cantarell;  
  FC_Font* amble;

// needs to be triggered whenever the UI scale changes
void init_fonts(float scale) {
  fc_load_font_from_ttf(cagliostro, renderer, TTF_OpenFont("../../fonts/Cagliostro-Regular.ttf", 8 * scale), BLACK);
  fc_load_font_from_ttf(cantarell, renderer, TTF_OpenFont("../../fonts/Cantarell-Regular.ttf", 8 * scale), BLACK);
  fc_load_font_from_ttf(amble, renderer, TTF_OpenFont("../../fonts/Amble-Regular.ttf", 8 * scale), BLACK);
}
// @codegen:end fonts

