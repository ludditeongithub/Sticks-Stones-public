#pragma once

// info section made up of several info boxes.

#include "SDL_FontCache.h"

#include "data/types/ui.hpp"
#include "display/render/sprite.hpp"
#include "display/render/texture.hpp"
#include "display/ui/aggregates/info_box.hpp"
#include "display/ui/components/element.hpp"
#include "display/ui/components/text.hpp"
#include "display/ui/fonts.hpp"
#include "data/types/buildable.hpp"
#include <SDL_events.h>
#include <variant>

struct InfoSection {
	static inline SCoord display_pos;
	static constexpr uint8_t FRAME_BORDER = 1;
	static inline SDL_Rect frame = sprite::uis[UISprite::InfoMenuItemFrame];
  static constexpr SCoord title_pos= {50, 13};
        static constexpr FC_Font** title_font = &cagliostro;
  static constexpr SDL_Rect desc_box = {15, 56, 40, 50};
  static constexpr FC_Font **desc_font = &cagliostro; 
	Text title;
	Text desc;

  InfoSection(const char* title, const char* desc);

        void render();
	void handle(SDL_Event *e);
};

struct RequirementsSection
{
  static inline SCoord pos;
  static inline SDL_Rect frame = sprite::uis[UISprite::RequirementFrame];
  // TODO: consider array
  std::vector<RequirementBox> reqs;

  RequirementsSection(std::vector<Displayable>& requirements)
  {
    reqs.reserve(requirements.size());
    int fa = 0;
	  for (size_t i = 0; i < requirements.size(); i++)
	    {
	      reqs.emplace_back(RequirementBox{{pos.x, pos.y + fa}, requirements[i]});
	      fa += frame.y;
         }
  }
  
  void render();  
  void handle(SDL_Event *e);
};

struct RolesSection {
  static inline SCoord pos;
  static inline SDL_Rect frame = sprite::uis[UISprite::RoleFrame];
  static inline std::vector<RoleBox> reqs;

  RolesSection();

  void render();
  void handle(SDL_Event *e);
};
