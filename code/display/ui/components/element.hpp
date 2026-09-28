#pragma once
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_rect.h>

#include <display/render/sprite.hpp>
#include <display/render/screen.hpp>
#include <display/render/texture.hpp>

struct UIElement
{
	SCoord position; // left corner
	SDL_Rect source;
        UIElement(UISprite ui_sprite, SCoord position) : position(position), source(sprite::uis[ui_sprite])
	{}

        inline void render(SDL_Rect* viewport) { sprite_sheet_texture.render(position.x, position.y, &source, viewport); }
        inline void render() { sprite_sheet_texture.render(position.x, position.y, &source, g_main_screen_viewport); }
  
};

struct ElementTable {
  // each frame is one item. a frame may be a text box or a frame or even frameless
    int DISPLAY_X;
    int DISPLAY_Y;
    int FRAME_W;
    int FRAME_H;
    int FRAME_GAP_W;
    int FRAME_GAP_H;
    int ROW_LENGTH;
    int FRAME_AMOUNT;

  constexpr SCoord get_position(int element_number) const {
    return {DISPLAY_X + ((FRAME_W + FRAME_GAP_W) * (element_number % ROW_LENGTH)), DISPLAY_Y + ((FRAME_H + FRAME_GAP_H) * (element_number / ROW_LENGTH))};
  }

  constexpr int get_end_x() const { return DISPLAY_X + (FRAME_W * ROW_LENGTH + FRAME_GAP_W * (ROW_LENGTH - 1)); }
};
