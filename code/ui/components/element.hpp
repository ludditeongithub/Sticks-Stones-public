#pragma once
#include <render/screen.hpp>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <core/data.hpp>
#include <render/animation.hpp>
#include <render/sprite.hpp>

enum class UISprite
{
	WoodTextBox,
	EntityDisplayFrame,
        EquipmentFrame,
        RoleFrame,
	MAX
};

struct UIElement
{
	SCoord position; // left corner
	SDL_Rect *source;

  void render(SDL_Rect viewport) { renderer->render(position.x, position.y, source, &viewport); }
        inline void render() { renderer->render(position.x, position.y, source, g_main_screen_viewport); }
  
};

struct ElementTable {
  // each frame is one item. a frame may be a text box or a frame or even frameless
   constexpr int DISPLAY_X;
   constexpr int DISPLAY_Y;
   constexpr int FRAME_W;
   constexpr int FRAME_H;
   constexpr int FRAME_GAP_W;
   constexpr int FRAME_GAP_H;
   constexpr int ROW_LENGTH;
   constexpr int FRAME_AMOUNT;

  SCoord get_position(int element_number) {
    return {DISPLAY_X + ((FRAME_W + FRAME_GAP_W) * (element_number % ROW_LENGTH)), DISPLAY_Y + ((FRAME_ + FRAME_GAP_W) * (element_number / ROW_LENGTH))};
  }
};
