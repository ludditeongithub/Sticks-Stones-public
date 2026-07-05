#pragma once
#include <string>
#include <vector>
#include <extern/SDL_FontCache.h>
#include <SDL2/SDL_render.h>
#include "button.hpp"
#include <render/screen.hpp>
#include "text.hpp"

SDL_Rect popUpBoxSprite = {};

struct PopUpBox {
  std::string message;
  std::vector<ButtonUI> options;
  Text text;
  uint16_t horizontalPadding;
  Coord topLeftCorner;

  void render()
  {
	  spriteSheetTexture.render(topLeftCorner.x, topLeftCorner.y, &popUpBoxSprite, viewport);
          SDL_RenderSetViewport(renderer, viewport);
          FC_DrawColor(text.font, renderer, topLeftCorner.x + horizontalPadding, topLeftCorner.y, text.color, text.text);
  }
};
