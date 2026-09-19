#pragma once
#include <SDL2/SDL_rect.h>

struct DisplayInfo
{
  SDL_Rect display;
  const char *title;
  const char* desc;
};
