#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SDL2/SDL.h>

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

constexpr uint32_t TILE_LENGTH = 16;
constexpr uint32_t SCREEN_TILE_HEIGHT = SCREEN_HEIGHT / TILE_LENGTH;
constexpr uint32_t SCREEN_TILE_WIDTH = SCREEN_WIDTH / TILE_LENGTH;

#endif
