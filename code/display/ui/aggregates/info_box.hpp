#pragma once

#include "display/render/sprite.hpp"
#include "display/ui/fonts.hpp"
#include "data/types/buildable.hpp"
#include <display/render/sprite.hpp>
#include <data/types/unit.hpp>
#include <display/ui/components/display_frame.hpp>
#include <display/ui/components/text.hpp>
#include <SDL_FontCache.h>

// info box is all info on one thing that appears in a requirements or roles list.
using Displayable = std::variant<Item, Buildable, knowledge::Academic, knowledge::Technology>;

struct RequirementBox {
  SDL_Rect source;
  SCoord pos;
  static inline FC_Font* font = cagliostro;
  constexpr static int FRAME_TEXT_GAP = 2;

  RequirementBox(SCoord pos, Displayable displayable) : pos(pos)
  {
	  source = sprite::get_displayable(displayable);
  }

  inline void render(SDL_Rect frame)
  {
    sprite_sheet_texture::render(pos.x, pos.y, frame);
    sprite_sheet_texture::render(pos.x, pos.y, source);	  
  }
};

struct ProductionRequirementBox : RequirementBox {
  uint16_t& amount;
  uint16_t &inventory_total;
  
};

struct RoleBox {
  const Role role;
  uint16_t total_amount = 0;
  uint16_t amount_avail = 0;
  SCoord pos;

  inline void render(SDL_Rect& frame)
  {
    sprite_sheet_texture::render(pos.x, pos.y, frame);          
          SDL_Rect source = sprite::roles[role];
          sprite_sheet_texture::render(pos.x, pos.y, source);
  }
};
