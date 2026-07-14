#include "texture.hpp"
#include "window.hpp"

LTexture::LTexture()
{
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
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
		new_texture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
		if (new_texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
			       SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}

	// Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	// Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect *clip, SDL_Rect *viewport)
{

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		viewport->w = clip->w;
		viewport->h = clip->h;
	}

	// Render to screen
	SDL_RenderCopy(gRenderer, mTexture, clip, viewport);
}

int LTexture::get_width() { return mWidth; }

int LTexture::get_height() { return mHeight; }
