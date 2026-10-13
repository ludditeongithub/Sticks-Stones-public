#pragma once
#include "core/math.hpp"
#include "random.hpp"
#include <cassert>
#include <cstdint>
#include <SDL2/SDL_rect.h>
#include <cmath>
#include <array>
#include <optional>

enum class Adjacency 
{
		Any,
		Horizontal,
		Vertical
};

enum class Direction : uint8_t
{
	North = 0,
	South = 1,
	East = 2,
	West = 3
};     

struct Coord
{	    
  uint32_t x;
  uint32_t y;   
		Coord operator+(const Coord c) { return Coord(this->x + c.x, this->y + c.y); }

		void operator+=(const Coord c) { this->x += c.x; this->y += c.y; }

		Coord operator-(const Coord c) { return Coord(this->x - c.x, this->y - c.y); }

		void operator-=(const Coord c) { this->x -= c.x; this-> y -= c.y; }

		Coord operator*(uint32_t s) { return Coord(this->x * s, this->y * s); }

		void operator*=(uint32_t s)
		{
			this->x *= s;
			this->y *= s;
		}

		bool operator!=(Coord c)
		{
				return this->x == c.x && this->y == c.y;
		}
};

struct Rect
{
		uint32_t x, y, w, h;
		// x, y as top left corner
};

  template<typename T>
  SDL_Rect make_sdl_rect(T x, T y, T w, T h)
   {
     return {static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)};
   }

struct SCoord
{
	int x;
	int y;

	SCoord operator*=(uint32_t s)
	{
		return SCoord(this->x * s, this->y * s);
	}
};

std::array<SCoord, 4> directions = {
    SCoord{-1, 0},
    SCoord{1, 0},
    SCoord{0, -1},
    SCoord{0, 1}
  };

inline uint32_t coord_to_index(Coord c) { return c.x + c.y * c.y; }

inline bool adjacent(Coord start, Coord next, Adjacency adjacency = Adjacency::Any) {
		switch (adjacency) {
		case Adjacency::Horizontal:
       			if ((start.x - next.x) == 1 && (start.y - next.y) == 0) return true;
				break;
		case Adjacency::Vertical:
       			if ((start.y - next.y) == 1 && (start.x - next.x) == 0) return true;
       			break;
		default:
		if (((start.y - next.y) <= 1 && (start.x - next.x) == 0) || ((start.x - next.x) == 1 && (start.y - next.y) == 0)) return true;
		}
		return false;
}

inline bool adjacent_coords(Coord first, Coord second)
{
	return ((static_cast<int>(first.x - second.x)) <= 1 &&
		(static_cast<int>(first.y - second.y)) <= 1);
}

Direction get_random_adj_direction(Direction direction)
{
	if (direction == Direction::North)
	{
	  if (random_bool->next())
			return Direction::East;
		return Direction::West;
	}
	if (direction == Direction::South)
	{
		if (random_bool->next())
			return Direction::East;
		return Direction::West;
	}
	if (direction == Direction::West)
	{
		if (random_bool->next())
			return Direction::North;
		return Direction::South;
	}
	if (random_bool->next())
		return Direction::North;
	return Direction::South;
}

template <typename T> T chebyshev(T x1, T y1, T x2, T y2)
{
	return std::max((x2 - x1), (y2 - y1));
}

template <typename T> inline T euclidean_dist(T x1, T y1, T x2, T y2)
{
	return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

inline uint32_t manhattan_dist(Coord x, Coord y)
{
	return unsigned_abs_diff(x.y , y.y) + unsigned_abs_diff(x.x , y.x);
}

uint32_t manhattan_dist(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) { return unsigned_abs_diff(x1 , x2) + unsigned_abs_diff(y1 , y2); }

std::optional<Direction> adj_check_tile(Coord subject, Coord target)
{
	if (manhattan_dist(subject, target) > 1)
		return std::nullopt;
	if (subject.y - target.y == 1)
		return std::make_optional<Direction>(Direction::East);
	if (subject.y - target.y == -1)
		return std::make_optional<Direction>(Direction::West);
	if (subject.x - target.x == 1)
		return std::make_optional<Direction>(Direction::North);
	if (subject.x - target.x == -1)
		return std::make_optional<Direction>(Direction::South);
	return std::nullopt;
}

