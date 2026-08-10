#pragma once
#include <core/data.hpp>
#include <string>
#include <cstdint>
#include <SDL_FontCache.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <render/screen.hpp>

struct PositionedText
{
	FC_Font *font;
  SDL_Color color = {10,10,10};
	const char* text;
	Coord position;
};

struct Text {
	FC_Font *font;
	SDL_Color color = {10, 10, 10};
        SDL_Rect position;
	const char *text;

  void render(const SDL_Rect &viewport)
	{
		fc_draw_color(font, renderer, position.x, position.y, color, text);
	}
};
