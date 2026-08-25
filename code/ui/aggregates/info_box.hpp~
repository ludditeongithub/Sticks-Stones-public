#pragma once
#include "core/data.hpp"
#include <render/sprite_sheet_settings.hpp>
#include <world/item/description.hpp>
#include <world/buildable/description.hpp>
#include <world/unit/enum.hpp>
#include <ui/components/display_frame.hpp>
#include <ui/components/text.hpp>

// info box is all info on one thing that appears in a requirements or roles list.

struct ItemRequirement {
  Item item;
  uint16_t amount;
};

struct StationRequirement {
  Buildable buildable;
  uint16_t amount;
};

struct RequirementBox {
  std::variant<ItemRequirement, StationRequirement> req;
  SCoord pos;

  inline void render(SDL_Rect& frame, SDL_Rect& viewport)
  {
	  sprite_sheet_texture.render(pos.x, pos.y, &frame, viewport);
          
          SDL_Rect source;
	  if (auto c = std::get_if<ItemRequirement>(&req))
	  {
            source = sprite::item_sprites[c->item];
	  }
	  else if (auto c = std::get_if<StationRequirement>(&req))
	  {
            source = sprite::buildable[c->buildable];
          }
          sprite_sheet_texture.render(pos.x, pos.y, &source, viewport);
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
