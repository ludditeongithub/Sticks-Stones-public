#pragma once
#include <string>
#include <vector>
#include <SDL_FontCache.h>
#include <SDL2/SDL_render.h>
#include "button.hpp"
#include <render/screen.hpp>
#include "text.hpp"

SDL_Rect pop_up_box_sprite = {};

struct PopUpBox {
  std::string message;
  std::vector<ButtonUI> options;
  Text text;
  uint16_t horizontal_padding;
  Coord top_left_corner;

  void render()
  {
	  sprite_sheet_texture.render(top_left_corner.x, top_left_corner.y, &pop_up_box_sprite, viewport);
          SDL_RenderSetViewport(renderer, viewport);
          fc_draw_color(text.font, renderer, top_left_corner.x + horizontal_padding, top_left_corner.y, text.color, text.text);
  }
};
