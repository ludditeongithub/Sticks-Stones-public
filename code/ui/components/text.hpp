#pragma once
#include <core/data.hpp>
#include <string>
#include <cstdint>
#include <extern/SDL_FontCache.h>
#include <SDL2/SDL_pixels.h>

struct PositionedText
{
	FC_Font* font;
	const char* text;
	SDL_Color color;
	Coord position;
};

struct Text {
	FC_Font* font;
	const char* text;
	SDL_Color color;
};
