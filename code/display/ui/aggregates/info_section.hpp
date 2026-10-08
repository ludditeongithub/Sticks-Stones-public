#pragma once

// info section made up of several info boxes.

#include "SDL_FontCache.h"

#include "display/render/sprite.hpp"
#include "display/render/texture.hpp"
#include "display/ui/aggregates/info_box.hpp"
#include "display/ui/components/element.hpp"
#include "display/ui/components/text.hpp"
#include "display/ui/fonts.hpp"
#include "data/types/buildable.hpp"
#include <variant>

struct InfoSection {
	static inline SCoord display_pos;
	static constexpr uint8_t FRAME_BORDER = 1;
	static inline SDL_Rect frame = sprite::uis[UISprite::InfoMenuItemFrame];
  static constexpr SCoord title_pos= {50, 13};
        static constexpr FC_Font** title_font = &cagliostro;
  static constexpr SDL_Rect desc_box = {15, 56, 40, 50};
  static constexpr FC_Font **desc_font = &cagliostro;
  SDL_Rect display; 
	Text title;
	Text desc;

  InfoSection(SDL_Rect display, const char* title, const char* desc);

  void render(SDL_Rect& viewport);
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

    } else if (auto ptr = if (get_if<knowledge::Academic>(&display)) {
        
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

  RolesSection();

  void render(SDL_Rect &viewport);  
};
