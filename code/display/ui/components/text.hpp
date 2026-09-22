#pragma once
#include <data/types/aliases.hpp>
#include <string>
#include <cstdint>
#include <SDL_FontCache.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <display/render/screen.hpp>

enum class Alignment
{
	Left,
        Center,
	Right
};

inline FC_AlignEnum cast_align(Alignment alignment) {
  switch (alignment) {
  case Alignment::Left:
    return FC_ALIGN_LEFT;
    break;
  case Alignment::Center:
    return FC_ALIGN_CENTER;
    break;
  case Alignment::Right:
    return FC_ALIGN_RIGHT;
    break;
  default:
    
  }

}

constexpr int ALIGNMENT_INDENT_RATIO = 26;

struct PositionedText
{
	FC_Font *font;
	const char* text;
	Coord position;
};

SCoord get_abs_text_alignment_pos(SDL_Rect container, Alignment alignment)
    {
      switch (alignment) {
      case Alignment::Left:
        return {container.x + (container.w / ALIGNMENT_INDENT_RATIO), container.y + (container.h / 2)}; 
        break;
      case Alignment::Center:
        return {container.x + (container.w / 2), container.y + container.h / 2)};
        break;
      case Alignment::Right:
        return {container.x + container.w - (container.w / ALIGNMENT_INDENT_RATIO), container.y + container.h / 2)};
        break;
      default:
      }
    }

SCoord get_text_alignment_pos(SCoord dimensions, Alignment alignment) {
  switch (alignment) {
      case Alignment::Left:
        return {(dimensions.x / ALIGNMENT_INDENT_RATIO), (dimensions.y / 2)}; 
        break;
      case Alignment::Center:
        return {(dimensions.x / 2), dimensions.y / 2)};
        break;
      case Alignment::Right:
        return {dimensions.x - (dimensions.x / ALIGNMENT_INDENT_RATIO), dimensions.y / 2)};
        break;
      default:
      }
}

struct Text {
	FC_Font *font;
	const char *text;
  
	Text(FC_Font *font, const char *text = "") {}

  void render(const SDL_Rect &viewport, SCoord position, Alignment alignment)
  {
    fc_draw_align(font, renderer, position.x, position.y, cast_align(alignment), text);
  }

  void render(const SDL_Rect &viewport, SDL_Rect box, Alignment alignment) 
  {
    fc_draw_box_align(font, renderer, box, cast_align(alignment), text);
  }
};
