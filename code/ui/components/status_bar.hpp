#include <SDL2/SDL_rect.h>
#include <core/data.hpp>
#include <render/texture.hpp>

// TODO

struct StatusBar
{
	int max;
	int current;
	const SDL_Rect *fullBar;
	const SDL_Rect *emptyBar;
	const SCoord position; // left corner
	bool horizontal;

	StatusBar(SCoord position, const SDL_Rect *fullBar, const SDL_Rect *emptyBar,
		  bool horizontal)
	    : fullBar(fullBar), emptyBar(emptyBar), position(position), horizontal(horizontal)
	{
	}

	void render(SDL_Rect viewport)
	{
		// TODO: error
		float portion = current / max;

		if (horizontal)
		{
			int fullLength = fullBar->w;
			int unfixed = fullBar->h;
		}
		else
		{
			int fullLength = fullBar->h;
			int unfixed = fullBar->w;
		}

		int filledLength = portion * fullLength;
		int unfilledLength = fullLength - filledLength;

		if (horizontal)
		{
			SDL_Rect unfilledClip = {emptyBar->x, emptyBar->y, filledLength, unfixed};
			SDL_Rect filledClip = {fullBar->x, fullBar->y, filledLength, unfixed};

			gSpriteSheetTexture.render(position.x, position.y, &unfilledClip,
						   &viewport);
			gSpriteSheetTexture.render(position.x + unfilledLength, position.y,
						   &filledClip, &viewport);
		}
		else
		{
			SDL_Rect unfilledClip = {emptyBar->x, emptyBar->y, unfixed, filledLength};
			SDL_Rect filledClip = {fullBar->x, fullBar->y, unfixed, filledLength};

			gSpriteSheetTexture.render(position.x, position.y, &unfilledClip,
						   &viewport);
			gSpriteSheetTexture.render(position.x, position.y + unfilledLength,
						   &filledClip, &viewport);
		}
	}
};
