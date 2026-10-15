#include "core/tables.hpp"
#include "data/types/ui.hpp"
#include "display/ui/main/bottom_strip.hpp"
#include <SDL2/SDL_rect.h>
#include <display/render/texture.hpp>
#include <display/render/sprite.hpp>
#include <variant>
#include <core/coord.hpp>

namespace status_bar
  {

  enum class Entity
  {
	  Unit,
	  Plant,
	  Animal,
	  Item,
	Aggregate
};

enum class Type
{
	Health,
	Thirst,
	Hunger,
	Satisfaction,
	Temperature,
	Sunlight,
	Water,
	MAX
};    

constexpr int EMPTY_HORIZONTAL_OFFSET; 

RuntimeLookupTable<status_bar::Type, int> vertical_sprite_offsets;

SDL_Rect get_status_bar_sprite(status_bar::Entity entity, status_bar::Type type, bool full)
{
  using enum status_bar::Type;
  switch (entity) {
  case status_bar::Entity::Unit:
    switch (type) {
    case Satisfaction:
    case Health:
    case Hunger:
    case Temperature:
    case Thirst:
      break;
    default:
      assert(!"Tried to get invalid status bar sprite type for Unit.");
    }
    break;
  case status_bar::Entity::Plant:
    switch(type) {
  case Health:
  case Water:
  case Sunlight:
      break;
  default: assert(!"Tried to get invalid status bar sprite type for Plant.");
    }
    break;
  case status_bar::Entity::Animal:
    switch(type) {
  case Health:
  case Hunger:
  case Thirst:
    break;
    default: assert(!"Tried to get invalid status bar sprite type for Animal.");
    }
    break;
  case status_bar::Entity::Item:
    switch (type) {
    case Health:
      break;
    default: assert(!"Tried to get invalid status bar sprite type for Animal.");    
    }
    break;
  case status_bar::Entity::Aggregate:
    switch (type) {
  case Health:
  case Thirst:
  case Hunger:
  case Satisfaction:
    case Temperature:
      break;
    default:
          assert(!"Tried to get invalid status bar sprite type for Aggregate.");
    }
    break;
  default: assert("Tried to use display status bars for invalid Entity.");
  }
  SDL_Rect r = sprite::uis[UISprite::StatusBar];
  if (full)
    r.x += EMPTY_HORIZONTAL_OFFSET;
  r.y += vertical_sprite_offsets[type];
  return r;
}


// TODO
using Variant = std::variant<Unit, Animal, Plant, Aggregate>;

struct Bar
{
        
	SDL_Rect full_bar;
        SDL_Rect empty_bar;
	int max;
	int current;
	const SCoord position; // left corner
	const bool horizontal;
       // const bool aggregate;

  const SDL_Rect& viewport;

        Bar(status_bar::Entity entity, status_bar::Type type, const SCoord position, const bool horizontal, const SDL_Rect& viewport)
    : position(position), horizontal(horizontal), viewport(viewport)
        {
	  full_bar = get_status_bar_sprite(entity, type, true);
          empty_bar = get_status_bar_sprite(entity, type, false);
	}

	void render(SDL_Rect viewport)
	{
		// TODO: error
		float portion = current / max;
		int full_length;
                int unfixed;

		if (horizontal)
		{
			full_length = full_bar.w;
			unfixed = full_bar.h;
		}
		else
		{
			full_length = full_bar.h;
			unfixed = full_bar.w;
		}

		int filled_length = portion * full_length;
		int unfilled_length = full_length - filled_length;

		if (horizontal)
		{
			SDL_Rect unfilled_clip = {empty_bar.x, empty_bar.y, filled_length, unfixed};
			SDL_Rect filled_clip = {full_bar.x, full_bar.y, filled_length, unfixed};

		        sprite_sheet_texture::render(position.x, position.y, unfilled_clip);
		        sprite_sheet_texture::render(position.x + unfilled_length, position.y, filled_clip);
		}
		else
		{
			SDL_Rect unfilled_clip = {empty_bar.x, empty_bar.y, unfixed, filled_length};
			SDL_Rect filled_clip = {full_bar.x, full_bar.y, unfixed, filled_length};

		        sprite_sheet_texture::render(position.x, position.y, unfilled_clip);
		        sprite_sheet_texture::render(position.x, position.y + unfilled_length, filled_clip);
		}
	}
};

};
