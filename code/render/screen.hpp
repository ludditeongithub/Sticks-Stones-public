#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <core/data.hpp>
#include <array>
#include <SDL2/SDL.h>

// The window we'll be rendering to
SDL_Window *window = NULL;

// The window renderer
SDL_Renderer *renderer = NULL;

// VIEWPORTS
SDL_Rect g_main_screen_viewport = {0, 0, 640, 320};
const int first_launch_window_width = 200;
const int first_launch_window_height = 500;

// Game Simulation screen dimensions, before upscale to user screen
constexpr int screen_width = 640;
constexpr int screen_height = 480;

constexpr uint32_t TILE_LENGTH = 16;
constexpr uint32_t SCREEN_TILE_HEIGHT = screen_height / TILE_LENGTH;
constexpr uint32_t SCREEN_TILE_WIDTH = screen_width / TILE_LENGTH;

std::array<Coord, 6> screen_dimensions = {Coord{640, 360},  {1280, 720},  {1366, 768},
					  {1600, 900}, {1920, 1080}, {3840, 2160}};

std::array<Coord, 6> adjusted_screen_dimensions = {Coord{640, 360}, {1280, 720},  {1920, 1080},		    {2560, 1440}, {3200, 1800}, {3840, 2160}};

#endif
