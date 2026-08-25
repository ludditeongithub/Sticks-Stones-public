#pragma once
#include "core/data.hpp"
#include "ui/fonts.hpp"
#include "world/buildable/enum.hpp"
#include <render/sprite_sheet_settings.hpp>
#include <world/item/description.hpp>
#include <world/buildable/description.hpp>
#include <world/unit/enum.hpp>
#include <ui/components/display_frame.hpp>
#include <ui/components/text.hpp>

// info box is all info on one thing that appears in a requirements or roles list.

using Displayable = std::variant<Item, Buildable>;

struct RequirementBox {
  Displayable req;
  uint16_t& amount;
  uint16_t& inventory_total;
  SCoord pos;
  static inline FC_Font* font = cagliostro_4;
  constexpr static int FRAME_TEXT_GAP = 2;

  inline void render(SDL_Rect& frame, SDL_Rect& viewport)
  {
	  sprite_sheet_texture.render(pos.x, pos.y, &frame, viewport);

	  // displayable
          SDL_Rect source;
	  if (auto c = std::get_if<Item>(&req))
	  {
            source = sprite::item[c];
	  }
	  else if (auto c = std::get_if<Buildable>(&req))
	  {
            source = sprite::buildable[c];
          }
	  sprite_sheet_texture.render(pos.x, pos.y, &source, viewport);

	  // text info
          std::string text = std::to_string(amount) + " / " + std::to_string(inventory_total);
	  fc_draw_align(font, renderer, pos.x + frame.x + FRAME_TEXT_GAP, pos.y, cast_align(Alignment::Left), text.c_str());
	  
  }
};

struct RoleBox {
  const Role role;
  uint16_t total_amount = 0;
  uint16_t amount_avail = 0;
  SCoord pos;

  inline void render(SDL_Rect& frame, SDL_Rect& viewport)
  {
	  sprite_sheet_texture.render(pos.x, pos.y, &frame, viewport);          
          SDL_Rect source = sprite::roles[role];
          sprite_sheet_texture.render(pos.x, pos.y, &source, viewport);
  }
};
