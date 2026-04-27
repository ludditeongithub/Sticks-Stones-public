#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Current displayed texture
SDL_Texture *gTexture = NULL;

// Screen dimension constants
const int RAW_SCREEN_WIDTH = 480;
const int RAW_SCREEN_HEIGHT = 270;

// Starts up SDL and creates window
bool initWindow();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();
