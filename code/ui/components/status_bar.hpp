#include <SDL2/SDL_rect.h>
#include <core/data.hpp>
#include <render/texture.hpp>
#include <variant>

struct UnitStatusBar
{
	enum class Value
	{
		Health,
		Hunger,
		Thirst,
		Satisfaction,
		MAX
	};
  Value value = Value::Health;

  SDL_Rect get_full_sprite() { return unit_status_bars[value].full; }
  SDL_Rect get_empty_sprite() { return unit_status_bars[value].full; }
};

struct AnimalStatusBar
{
	enum class Value
	{
		Health,
		Hunger,
		Thirst,
		MAX
	};
  Value value = Value::Health;

  SDL_Rect get_full_sprite() { return animal_status_bars[value].full; }
  SDL_Rect get_empty_sprite() { return animal_status_bars[value].full; }
};

struct PlantStatusBar
{
	enum class Value
	{
		Health,
		Water,
                Sunlight,
		MAX
	};
  Value value = Value::Health;

  SDL_Rect get_full_sprite() { return plant_status_bars[value].full; }
  SDL_Rect get_empty_sprite() { return plant_status_bars[value].full; }
};


// TODO
using StatusBarVariant = std::variant<UnitStatusBar, AnimalStatusBar, PlantStatusBar>;

struct StatusBar
{
        
	SDL_Rect full_bar;
        SDL_Rect empty_bar;
	int max;
	int current;
	const SCoord position; // left corner
	const bool horizontal;

  const SDL_Rect& viewport;

        StatusBar(StatusBarVariant variant, const SCoord position, const bool horizontal, const SDL_Rect& viewport)
          : position(position), horizontal(horizontal), viewport(viewport)
	{          
          std::visit([this](auto& bar)
		{
			full_bar = bar.get_full_sprite();
                        empty_bar = bar.get_empty_sprite();
                },
            variant);    
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

			sprite_sheet_texture.render(position.x, position.y, &unfilled_clip,
						   viewport);
			sprite_sheet_texture.render(position.x + unfilled_length, position.y,
						   &filled_clip, viewport);
		}
		else
		{
			SDL_Rect unfilled_clip = {empty_bar.x, empty_bar.y, unfixed, filled_length};
			SDL_Rect filled_clip = {full_bar.x, full_bar.y, unfixed, filled_length};

			sprite_sheet_texture.render(position.x, position.y, &unfilled_clip,
						   viewport);
			sprite_sheet_texture.render(position.x, position.y + unfilled_length,
						   &filled_clip, viewport);
		}
	}
};
