#include "enum.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>

struct ScavengeableDatabase
{
	Array<Scavengeable> types;
	Array<Coord> coords;
}
