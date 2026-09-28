#pragma once
#include <cstdint>
#include <cmath>
#include <stdexcept>

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

inline void move(Direction direction)
		{
switch (direction) {
case Direction::North:
       	y -= 1;
       	break;
case Direction::South:
       	y += 1;
	    break;
case Direction::East:
       	x += 1;
       	break;
default:
		x -= 1;
        break;
}
		}			
};

struct SCoord
{
	int x;
	int y;

	SCoord operator*=(uint32_t s)
	{
		return SCoord(this->x * s, this->y * s);
	}
};

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

//TODO: consider stride
inline Coord get_pos(Direction direction, Coord coord, uint8_t stride = 1)
{
  Coord new_pos;
  switch (direction) {
  case Direction::North:
    new_pos = {coord.x, coord.y - stride};
    break;
  case Direction::South:
    new_pos = {coord.x, coord.y + stride};
    break;
  case Direction::East:
    new_pos = {coord.x + stride, coord.y};
    break;
  case Direction::West:
    new_pos = {coord.x - stride, coord.y};
    break;
  default:
  // TODO: error
    break;
  }
  return new_pos;
}

template <typename T> T chebyshev(T x1, T y1, T x2, T y2)
{
	return std::max((x2 - x1), (y2 - y1));
}

template <typename T> inline T euclidean_dist(T x1, T y1, T x2, T y2)
{
	return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

inline uint16_t manhattan_dist(Coord c1, Coord c2)
{
    int dx = static_cast<int>(c1.x) - static_cast<int>(c2.x);
    int dy = static_cast<int>(c1.y) - static_cast<int>(c2.y);

    return static_cast<uint16_t>((dx) + (dy));
}

template <typename T> inline float diff_mult(T value, T target, T bound)
{
	T range = abs(bound - target);
	T diff = abs(bound - value);
	return diff / range;
}

// Interpolations and Normalizations
inline auto remap = [](float x, float a, float b, float c, float d)
{ return c + (x - a) * (d - c) / (b - a); };

inline auto normalize(float x, float min, float max) { return (x - min) / (max - min); }


inline float lerp(float x1, float x2, float x3, float s1, float s2, float s3)
{
    if (s1 > 1.0 || s1 < 0.0 || s2 > 1.0 || s2 < 0.0 || s3 > 1.0 || s3 < 0.0)
        throw std::out_of_range("Linear Interpolation setting must be between 0.0 and 1.0");
    return std::lerp(std::lerp(x1, x2, s1), std::lerp(x2, x3, s2), s3);
}
