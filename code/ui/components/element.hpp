#ifndef UI_HPP
#define UI_HPP

#include <render/screen.hpp>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <core/data.hpp>
#include <render/animation.hpp>
#include <render/sprite.hpp>

enum class UISprite {
	MAX
};

struct UIElement
{
	SCoord position; // left corner
	SDL_Rect *src;

	void render(SDL_Rect viewport)
	{
		renderer->render(position.x, position.y, src, &viewport);
	}
};

#endif
