// Stores hot arrays of sprite data (positions, sizes, colors, texture IDs), handles batching logic
#include "sprite.hpp"
#include <core/data.hpp>

struct SpriteData
{
	Coord position;
	Coord dimensions;
	Sprite sprite;

	SpriteData(Coord position, Coord dimensions, Sprite sprite)
	    : position(position), dimensions(dimensions), sprite(sprite)
	{
	}
};
