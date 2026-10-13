#pragma once
#include <stdexcept>
#include <cmath>

template <typename T>
constexpr T unsigned_abs_diff(T a, T b)
{
    return a > b ? a - b : b - a;
}

template <typename T> inline float diff_mult(T value, T target, T bound)
{
	T range = unsigned_abs_diff(bound , target);
	T diff = unsigned_abs_diff(bound , value);
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

