// RANDOM
#include "data.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <functional>

// Distance and Coords
template <typename T> T chebyshev(T x1, T y1, T x2, T y2)
{
	return std::max(std::abs(x2 - x1), std::abs(y2 - y1));
}

template <typename T> inline T euclideanDist(T x1, T y1, T x2, T y2)
{
	return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

inline uint16_t manhattanDist(int x1, int x2, int y1, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
};

inline uint16_t manhattanDist(Coord c1, Coord c2)
{
	return std::abs(c1.x - c2.x) + std::abs(c1.y - c2.y);
};

template <typename T> inline float diffMult(T value, T target, T bound)
{
	T range = std::abs(bound - target);
	T diff = std::abs(bound - value);
	return diff / range;
}

// Interpolations and Normalizations
inline auto remap = [](float x, float a, float b, float c, float d)
{ return c + (x - a) * (d - c) / (b - a); };

inline auto normalize(float x, float min, float max) { return (x - min) / (max - min); }

inline float lerp(float x1, float x2, float s)
{
	if (s > 1.0 || s < 0.0)
		throw std::out_of_range("Linear Interpolation setting must be between 0.0 and 1.0");
	return (x1 * (1 - s)) + (x2 * s);
}

inline float lerp(float x1, float x2, float x3, float s1, float s2, float s3)
{
    if (s1 > 1.0 || s1 < 0.0 || s2 > 1.0 || s2 < 0.0 || s3 > 1.0 || s3 < 0.0)
        throw std::out_of_range("Linear Interpolation setting must be between 0.0 and 1.0");
    return lerp(lerp(x1, x2, s1), lerp(x2, x3, s2), s3);
}

// Custom hash function for pair<int, int>
struct hashPair
{
	uint16_t operator()(const std::pair<int, int> &p) const
	{
		auto h1 = std::hash<int>{}(p.first);
		auto h2 = std::hash<int>{}(p.second);
		return h1 ^ h2; // Combine the two hash values
	}
};

inline uint16_t hashCoords(int x, int y)
{
	auto h1 = std::hash<int>{}(x);
	auto h2 = std::hash<int>{}(y);
	return h1 ^ h2; // Same hash mixing logic as in the struct
}
