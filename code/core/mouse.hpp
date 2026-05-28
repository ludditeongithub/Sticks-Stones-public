#pragma once
#include "data.hpp"

bool mouseInside(SCoord mousePosition, SCoord topLeftCorner, SCoord dimensions) {
		bool inside = true;

		if( mousePosition.x < topLeftCorner.x )
		{
			inside = false;
		}
		else if( mousePosition.x > topLeftCorner.x + dimensions.x )
		{
			inside = false;
		}
		else if( mousePosition.y < topLeftCorner.y )
		{
			inside = false;
		}
		else if( mousePosition.y > topLeftCorner.y + dimensions.y )
		{
			inside = false;
		}
		return inside;
}
