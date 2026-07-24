#pragma once
#include <core/data.hpp>
#include <string>
#include <cstdint>
#include <SDL_FontCache.h>
#include <SDL2/SDL_pixels.h>

struct PositionedText
{
	FC_Font *font;
  SDL_Color color = {10,10,10};
	const char* text;
	Coord position;
};

struct Text {
	FC_Font *font;
        SDL_Color color = {10,10,10};
	const char* text;
};
