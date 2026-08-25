#include "core/entity.hpp"
#include "element.hpp"
#include "render/sprite_sheet_settings.hpp"
#include <render/screen.hpp>
struct DisplayFrame : UIElement {
	SDL_Rect entity_sprite;
  // frame sprite is source

  DisplayFrame(UISprite frame, Entity entity, SCoord position) : UIElement(frame, position)
  {
    entity_sprite = sprite::get(entity);
  }
  
	inline void render(const SDL_Rect viewport)
	{
          sprite_sheet_texture.render(position.x, position.y, source, viewport);		sprite_sheet_texture.render(position.x, position.y, &entity_sprite, viewport);
	}
	inline void change_display(Entity entity) { entity_sprite = sprite::get(entity); }
};

struct DoubleDisplayFrame : DisplayFrame
{
  bool second_entity = false;
  SDL_Rect second_entity_sprite;
  SDL_Rect second_frame_sprite;

  DoubleDisplayFrame(UISprite first_frame, UISprite second_frame, Entity first_entity, Entity second_entity, SCoord position) : DisplayFrame(first_frame, first_entity, position), second_entity_sprite(sprite::get(second_entity)), second_frame_sprite(sprite::ui_sprites[second_frame])
  {
    
  }

  inline void render(const SDL_Rect viewport)
  {
	  if (second_entity)
	  {
		  sprite_sheet_texture.render(position.x, position.y, &second_frame_sprite, viewport);
		  sprite_sheet_texture.render(position.x, position.y, &second_entity_sprite, viewport);            
	  }
	  else
	  {
            DisplayFrame::render(viewport);
          }
  }

  inline void switch_display()
  {
    second_entity = !second_entity;
  }

  inline void change_second_display(Entity entity)
  {
    second_entity_sprite = sprite::get(entity);
  }
};
