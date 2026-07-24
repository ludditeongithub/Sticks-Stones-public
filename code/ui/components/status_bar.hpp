#include <SDL2/SDL_rect.h>
#include <core/data.hpp>
#include <render/texture.hpp>

// TODO

struct StatusBar
{
	int max;
	int current;
	const SDL_Rect *full_bar;
	const SDL_Rect *empty_bar;
	const SCoord position; // left corner
	bool horizontal;

	StatusBar(SCoord position, const SDL_Rect *full_bar, const SDL_Rect *empty_bar,
		  bool horizontal)
	    : full_bar(full_bar), empty_bar(empty_bar), position(position), horizontal(horizontal)
	{
	}

	void render(SDL_Rect viewport)
	{
		// TODO: error
		float portion = current / max;

		if (horizontal)
		{
			int full_length = full_bar->w;
			int unfixed = full_bar->h;
		}
		else
		{
			int full_length = full_bar->h;
			int unfixed = full_bar->w;
		}

		int filled_length = portion * full_length;
		int unfilled_length = full_length - filled_length;

		if (horizontal)
		{
			SDL_Rect unfilled_clip = {empty_bar->x, empty_bar->y, filled_length, unfixed};
			SDL_Rect filled_clip = {full_bar->x, full_bar->y, filled_length, unfixed};

			sprite_sheet_texture.render(position.x, position.y, &unfilled_clip,
						   &viewport);
			sprite_sheet_texture.render(position.x + unfilled_length, position.y,
						   &filled_clip, &viewport);
		}
		else
		{
			SDL_Rect unfilled_clip = {empty_bar->x, empty_bar->y, unfixed, filled_length};
			SDL_Rect filled_clip = {full_bar->x, full_bar->y, unfixed, filled_length};

			sprite_sheet_texture.render(position.x, position.y, &unfilled_clip,
						   &viewport);
			sprite_sheet_texture.render(position.x, position.y + unfilled_length,
						   &filled_clip, &viewport);
		}
	}
};
