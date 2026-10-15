#include "info_section.hpp"
#include "display/render/texture.hpp"
#include <data/run/texture.hpp>


RolesSection::RolesSection(){
    for (size_t i = 0; i < reqs.size(); i++) {
	    reqs[i].pos.x = pos.x;
            reqs[i].pos.y = pos.y + frame.y;
    }
  }

void RolesSection::render()
{
  sprite_sheet_texture::render(pos.x, pos.y, frame);
	  for (auto x: reqs) x.render(frame);
}
}


InfoSection::InfoSection(SDL_Rect display, const char* title, const char* desc) {
		this->title = Text(*title_font, title);
        this->desc = Text(*desc_font, desc);
        }

	void RequirementsSection::render()
	{
    sprite_sheet_texture::render(pos.x, pos.y, frame);
    for (auto x: reqs) x.render(frame);  
	}

void InfoSection::render(){
    sprite_sheet_texture::render(display_pos.x, display_pos.y, frame);

                SDL_Rect r;
                if (auto i = get_if<Item>(&display)) {
                  r = sprite::items[i];
                } else if (auto i = get_if<Buildable>(&display)) {
                  r =  sprite::buildables[i];
                }
  sprite_sheet_texture::render(display_pos.x + FRAME_BORDER, display_pos.y + FRAME_BORDER, r);

                title.render(title_pos);

		desc.render(desc_box);
}


