#pragma once
#include "coord.hpp"
#include <SDL2/SDL_rect.h>

inline bool mouse_inside(SCoord mouse_position, SCoord top_left_corner, SCoord dimensions) {
		bool inside = true;

		if( mouse_position.x < top_left_corner.x )
		{
			inside = false;
		}
		else if( mouse_position.x > top_left_corner.x + dimensions.x )
		{
			inside = false;
		}
		else if( mouse_position.y < top_left_corner.y )
		{
			inside = false;
		}
		else if( mouse_position.y > top_left_corner.y + dimensions.y )
		{
			inside = false;
		}
		return inside;
}

inline bool mouse_inside(SDL_Rect* viewport, SCoord mouse_position, SCoord top_left_corner, SCoord dimensions) {
		bool inside = true;

		if( mouse_position.x < top_left_corner.x + viewport->x)
		{
			inside = false;
		}
		else if( mouse_position.x > top_left_corner.x + dimensions.x + viewport->x)
		{
			inside = false;
		}
		else if( mouse_position.y < top_left_corner.y + viewport->y)
		{
			inside = false;
		}
		else if( mouse_position.y > top_left_corner.y + dimensions.y + viewport->y)
		{
			inside = false;
		}
		return inside;
}


inline bool mouse_inside(SCoord mouse_position, SDL_Rect rect) {
		bool inside = true;

		if( mouse_position.x < rect.x )
		{
			inside = false;
		}
		else if( mouse_position.x > rect.x + rect.w )
		{
			inside = false;
		}
		else if( mouse_position.y < rect.y )
		{
			inside = false;
		}
		else if( mouse_position.y > rect.y + rect.h )
		{
			inside = false;
		}
		return inside;
}
