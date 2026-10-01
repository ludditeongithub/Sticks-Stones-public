#pragma once
#include <SDL2/SDL_render.h>
#include <core/coord.hpp>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
// TODO: check if should be in WindowSystem

extern std::array<Coord, 6> screen_dimensions;
extern std::array<Coord, 6> adjusted_screen_dimensions;
extern Coord g_screen_dimensions;

const int first_launch_window_width = 200;
const int first_launch_window_height = 500;

// Game Simulation screen dimensions, before upscale to user screen
constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

constexpr uint32_t TILE_LENGTH = 16;
constexpr uint32_t SCREEN_TILE_HEIGHT = SCREEN_HEIGHT / TILE_LENGTH;
constexpr uint32_t SCREEN_TILE_WIDTH = SCREEN_WIDTH / TILE_LENGTH;


