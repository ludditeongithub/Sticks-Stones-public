#ifndef UI_HPP
#define UI_HPP

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <core/data.hpp>
#include <render/animation.hpp>
#include <render/sprite.hpp>

struct UIElement
{
	SCoord position; // left corner
	SDL_Rect *src;

	void render(SDL_Rect viewport)
	{
		gSpriteSheetTexture.render(position.x, position.y, src, &viewport);
	}
};

#endif
