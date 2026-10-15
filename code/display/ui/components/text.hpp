#pragma once

#include "display/ui/colors.hpp"
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
    return FC_ALIGN_CENTER;
  }
  return FC_ALIGN_CENTER;;
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
        return {container.x + (container.w / 2), container.y + container.h / 2};
        break;
      case Alignment::Right:
        return {container.x + container.w - (container.w / ALIGNMENT_INDENT_RATIO), container.y + container.h / 2};
        break;
      default:
        return {container.x + (container.w / 2), container.y + container.h / 2};
      }
return {container.x + (container.w / 2), container.y + container.h / 2};
}

SCoord get_text_alignment_pos(SCoord dimensions, Alignment alignment) {
  switch (alignment) {
      case Alignment::Left:
        return {(dimensions.x / ALIGNMENT_INDENT_RATIO), (dimensions.y / 2)}; 
        break;
      case Alignment::Center:
        return {(dimensions.x / 2), dimensions.y / 2};
        break;
      case Alignment::Right:
        return {dimensions.x - (dimensions.x / ALIGNMENT_INDENT_RATIO), dimensions.y / 2};
        break;
      default:
        break;
      }
}

struct Text {
	FC_Font *font;
        FC_Effect effect;
	const char *text;
  
	Text(FC_Font *font, const char *text = "", FC_Effect effect = {FC_AlignEnum::FC_ALIGN_CENTER, {1.0, 1.0}, DARK_GREY}) {}

  void render(SCoord position)
  {
    FC_DrawEffect(font, renderer, position.x, position.y, effect, text);
  }

  void render(SDL_Rect box) 
  {
    FC_DrawBoxEffect(font, renderer, box, effect, text);
  }
};
