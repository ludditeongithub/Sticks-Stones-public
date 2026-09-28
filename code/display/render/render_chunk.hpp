#pragma once
#include <SDL2/SDL.h>
#include <core/coord.hpp>
#include <display/render/screen.hpp>

constexpr uint16_t RENDER_CHUNK_WIDTH = 4;
constexpr uint16_t RENDER_CHUNK_HEIGHT = 4;

SDL_Texture& render_chunk_texture(Coord left_corner)
{
	SDL_Texture *chunk_texture =
	    SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			      RENDER_CHUNK_WIDTH, RENDER_CHUNK_HEIGHT);
	
	SDL_SetRenderTarget(renderer, chunk_texture);
	
	
}	
