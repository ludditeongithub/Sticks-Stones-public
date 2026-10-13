#pragma once
#include <data/run/coord.hpp>
#include <data/run/camera.hpp>
#include <cassert>

inline SDL_Point get_camera_relative_point_from_coord(Coord c)
{
	assert((c.x < g_camera.x + g_camera.w || c.x > g_camera.x) &&
	  (c.y < g_camera.y + g_camera.h || c.y > g_camera.h));

        return {static_cast<int>(c.x - g_camera.x), static_cast<int>(c.y - g_camera.y)};
}
