// Load and manage textures (spritesheets / atlases), GPU handles, UVs
#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <string>

// Loads individual image as texture
SDL_Texture *load_texture(std::string path);

// Texture wrapper class
class LTexture
{
      public:
	// Initializes variables
	LTexture();

	// Deallocates memory
	~LTexture();

	// Loads image at specified path
	bool load_from_file(std::string path);

	// Deallocates texture
	void free();

	// Renders texture at given point
	void render(int x, int y, SDL_Rect *clip, SDL_Rect& viewport);

	// Gets image dimensions
	int get_width();
	int get_height();

      private:
	// The actual hardware texture
	SDL_Texture *m_texture;

	// Image dimensions
	int m_width;
	int m_height;
};

LTexture sprite_sheet_texture;
