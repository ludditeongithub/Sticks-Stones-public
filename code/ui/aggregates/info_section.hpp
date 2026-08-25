#pragma once

// info section made up of several info boxes.

#include "SDL_FontCache.h"
#include "core/data.hpp"
#include "render/sprite_sheet_settings.hpp"
#include "render/texture.hpp"
#include "ui/aggregates/info_box.hpp"
#include "ui/components/element.hpp"
#include "ui/components/text.hpp"
#include "ui/fonts.hpp"
#include "world/buildable/enum.hpp"
#include <variant>

struct InfoSection {
	static inline SCoord display_pos;
	static constexpr uint8_t FRAME_BORDER = 1;
	static inline SDL_Rect frame = sprite::ui[UISprite::InfoMenuItemFrame];
  static constexpr SCoord title_pos= {50, 13};
        static constexpr FC_Font** title_font = &cagliostro_4;
  static constexpr SDL_Rect desc_box = {15, 56, 40, 50};
  static constexpr FC_Font **desc_font = &cagliostro_4;
  Displayable display;  
	Text title;
	Text desc;

  InfoSection(Displayable display, const char* desc) : display(display)
  {
	  char *title;
    if (auto x = std::get_if<Item>(this->display)) {
                title = magic_enum::enum_name((x)).c_str();
    } else if (auto x = std::get_if<Buildable>(this->display)) {
                title = magic_enum::enum_name((x)).c_str();
    }
		this->title = Text(*title_font, title);
                this->desc = Text(*desc_font, desc);
        }

  void render(SDL_Rect& viewport)
  {
    //render frame
    sprite_sheet_texture.render(display_pos.x, display_pos.y, &frame, viewport);

    //render item
                SDL_Rect r;
                if (auto i = get_if<Item>(&display)) {
                  r = sprite::item[i];
                } else if (auto i = get_if<Buildable>(&display)) {
                  r =  sprite::buildable[i];
                }
		sprite_sheet_texture.render(display_pos.x + FRAME_BORDER,
                                            display_pos.y + FRAME_BORDER, &r, viewport);

                title.render(viewport, title_pos, Alignment::Left);

		desc.render(viewport, desc_box, Alignment::Left);
        }
};

struct RequirementsSection
{
  static inline SCoord pos;
  static inline SDL_Rect frame = sprite::ui[UISprite::RequirementFrame];
  std::vector<RequirementBox> reqs;

  RequirementsSection(Displayable display)
  {
    if (auto ptr = std::get_if<Item>(&display)) {
     reqs[i].req =  
    }
    else if (auto ptr = std::get_if<Buildable>(&display)) {

    }

    for (size_t i = 0; i < ; i++) {
	    reqs[i].pos.x = pos.x;
            reqs[i].pos.y = pos.y + frame.y;
    }
  }
  
  void render(SDL_Rect &viewport)
  {
	  sprite_sheet_texture.render(pos.x, pos.y, &frame, viewport);

	  for (auto x: reqs) x.render(frame, viewport);
  }
};

struct RolesSection {
  static inline SCoord pos;
  static inline SDL_Rect frame = sprite::ui[UISprite::RoleFrame];
  static inline std::vector<RoleBox> reqs;

  RolesSection() {
    for (size_t i = 0; i < reqs.size(); i++) {
	    reqs[i].pos.x = pos.x;
            reqs[i].pos.y = pos.y + frame.y;
    }
  }

  void render(SDL_Rect &viewport)
  {
	  sprite_sheet_texture.render(pos.x, pos.y, &frame, viewport);

	  for (auto x: reqs) x.render(frame, viewport);
  }  
};
