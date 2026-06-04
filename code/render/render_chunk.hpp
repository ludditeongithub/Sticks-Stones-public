#pragma once
#include "draw.hpp"

constexpr uint16_t RENDER_CHUNK_WIDTH = 4;
constexpr uint16_t RENDER_CHUNK_HEIGHT = 4;

SDL_Texture& renderChunkTexture(Coord leftCorner)
{
	SDL_Texture *chunkTexture =
	    SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			      RENDER_CHUNK_WIDTH, RENDER_CHUNK_HEIGHT);
	
	SDL_SetRenderTarget(renderer, chunkTexture);
	
	
}	
