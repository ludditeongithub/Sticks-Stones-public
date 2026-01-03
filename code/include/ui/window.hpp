#ifndef WINDOW_H_
#define WINDOW_H_

#include "string"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

constexpr int SCREEN_HEIGHT = 270;
constexpr int SCREEN_WIDTH = 480;

/* Global Variables */
//The window we'll be rendering to
SDL_Window* gWindow{ nullptr };

//The surface contained by the window
SDL_Surface* gScreenSurface{ nullptr };

//The image we will load and show on the screen
SDL_Surface* uiBackground{ nullptr };

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

SDL_Texture* loadTexture( std::string path );

#endif // WINDOW_H_
