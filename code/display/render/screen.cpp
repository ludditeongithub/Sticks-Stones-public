#include "screen.hpp"

#include <SDL_render.h>
#include <SDL_video.h>
#include <array>
#include "core/coord.hpp"

WindowSystem g_window_system = WindowSystem(SCREEN_WIDTH, SCREEN_HEIGHT, false);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Rect main_screen_viewport = {0, 0, 640, 320};
SDL_Rect* g_main_screen_viewport = &main_screen_viewport;

std::array<Coord, 6> screen_dimensions = {{
    {640, 360},
    {1280, 720},
    {1366, 768},
    {1600, 900},
    {1920, 1080},
    {3840, 2160}
}};

std::array<Coord, 6> adjusted_screen_dimensions = {{
    {640, 360},
    {1280, 720},
    {1920, 1080},
    {2560, 1440},
    {3200, 1800},
    {3840, 2160}
}};
