#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <core/data.hpp>
#include <array>
#include <SDL2/SDL.h>

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Current displayed texture
SDL_Texture *gTexture = NULL;

// Game Simulation screen dimensions, before upscale to user screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

constexpr uint32_t TILE_LENGTH = 16;
constexpr uint32_t SCREEN_TILE_HEIGHT = SCREEN_HEIGHT / TILE_LENGTH;
constexpr uint32_t SCREEN_TILE_WIDTH = SCREEN_WIDTH / TILE_LENGTH;

std::array<Coord, 6> screen_dimensions = {Coord{640, 360},  {1280, 720},  {1366, 768},
					  {1600, 900}, {1920, 1080}, {3840, 2160}};

std::array<Coord, 6> adjusted_screen_dimensions = {Coord{640, 360}, {1280, 720},  {1920, 1080},
						   {2560, 1440}, {3200, 1800}, {3840, 2160}};

#endif
