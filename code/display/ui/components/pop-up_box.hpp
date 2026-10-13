#pragma once
#include <string>
#include <vector>
#include <SDL_FontCache.h>
#include <SDL2/SDL_render.h>
#include <display/ui/components/button.hpp>
#include <display/render/screen.hpp>
#include "text.hpp"

SDL_Rect pop_up_box_sprite = {};
struct ButtonUI;

struct PopUpBox {
  std::string message;
  std::vector<ButtonUI> options;
  Text text;
  SDL_Rect box;
  
  void render(SDL_Rect* viewport)
  {
	  SDL_RenderCopy(box.x, box.y, &pop_up_box_sprite, viewport);
          SDL_RenderSetViewport(renderer, viewport);
          FC_DrawBoxEffect(text.font, renderer, box, text.effect, text.text);
  }
};
