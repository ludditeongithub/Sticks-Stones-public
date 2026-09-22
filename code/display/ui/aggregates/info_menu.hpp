#pragma once
#include "info_section.hpp"
#include "info_box.hpp"
#include <display/ui/components/element.hpp>
#include <display/ui/components/display_frame.hpp>
#include <display/ui/components/text.hpp>

struct ProductionInfoMenu
{
	static inline SCoord pos;
	static inline SDL_Rect background;
  struct FullMenu {
        InfoSection infos; 
        RequirementsSection reqs;  
	RolesSection roles;
  };
  std::vector<FullMenu> menus; // contains objects for all possible produced items 
  
	void render(Item item)
	{
          
        }
};

