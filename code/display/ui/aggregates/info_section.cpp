#include "info_section.hpp"

void RolesSection::render(SDL_Rect &viewport){
	  SDL_RenderCopy(pos.x, pos.y, &frame, viewport);

	  for (auto x: reqs) x.render(frame, viewport);
  }

RolesSection::RolesSection(){
    for (size_t i = 0; i < reqs.size(); i++) {
	    reqs[i].pos.x = pos.x;
            reqs[i].pos.y = pos.y + frame.y;
    }
  }

void InfoSection::render(SDL_Rect& viewport){
    //render frame
    SDL_RenderCopy(display_pos.x, display_pos.y, &frame, viewport);

    //render item
                SDL_Rect r;
                if (auto i = get_if<Item>(&display)) {
                  r = sprite::item[i];
                } else if (auto i = get_if<Buildable>(&display)) {
                  r =  sprite::buildable[i];
                }
		SDL_RenderCopy(display_pos.x + FRAME_BORDER,
                                            display_pos.y + FRAME_BORDER, &r, viewport);

                title.render(viewport, title_pos, Alignment::Left);

		desc.render(viewport, desc_box, Alignment::Left);
        }

InfoSection::InfoSection(SDL_Rect display, const char* title, const char* desc) {
		this->title = Text(*title_font, title);
        this->desc = Text(*desc_font, desc);
        }
