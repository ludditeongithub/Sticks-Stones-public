#include "texture.hpp"

#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL_rect.h>

#include "screen.hpp"
#include "SDL_error.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_surface.h"

LTexture::LTexture()
{
	// Initialize
	m_texture = NULL;
	m_width = 0;
	m_height = 0;
}

LTexture::~LTexture()
{
	// Deallocate
	free();
}

bool LTexture::load_from_file(std::string path)
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture *new_texture = NULL;

	// Load image at specified path
	SDL_Surface *loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
		       IMG_GetError());
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loaded_surface, SDL_TRUE,
				SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
		if (new_texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
			       SDL_GetError());
		}
		else
		{
			// Get image dimensions
			m_width = loaded_surface->w;
			m_height = loaded_surface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}

	// Return success
	m_texture = new_texture;
	return m_texture != NULL;
}

void LTexture::free()
{
	// Free texture if it exists
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect *clip, SDL_Rect* viewport)
{

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		viewport->w = clip->w;
		viewport->h = clip->h;
	}

	// Render to screen
	SDL_RenderCopy(renderer, m_texture, clip, viewport);
}

int LTexture::get_width() { return m_width; }

int LTexture::get_height() { return m_height; }

LTexture sprite_sheet_texture = LTexture();
