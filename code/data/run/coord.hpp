#pragma once
#include "display/render/draw.hpp"
#include <data/const/chunk_data.hpp>
#include <core/coord.hpp>
#include <cstdint>
#include <vector>

namespace coord {
   uint16_t length_chunks;
   uint16_t height_chunks;
   uint16_t chunk_amount;
   uint32_t tile_amount;
   uint32_t tile_length;
   //TODO: non-square worlds
   uint16_t chunk_latitude_height = height_chunks / LATITUDE_TOTAL;
   uint16_t chunk_longitude_width = length_chunks / LONGITUDE_TOTAL;
   uint16_t equator;   

   void init(uint16_t lc, uint16_t hc)
  {
    length_chunks = lc;
    height_chunks = hc;
    chunk_amount = length_chunks * height_chunks;
    tile_amount = length_chunks * height_chunks * CHUNK_SIZE;
    tile_length = sqrt(tile_amount);
    equator = tile_length / 2;
  }

  inline bool out_of_bounds(Coord candidate)
  {
    return candidate.x < tile_length && candidate.y < tile_length;
  }

   inline Coord tile_to_chunk(Coord c) { return {c.x / CHUNK_LENGTH, c.y / CHUNK_LENGTH}; }

   inline Coord chunk_index_to_chunk(uint32_t index)
   {
	return {index % CHUNK_LENGTH, index / CHUNK_LENGTH};
   }

   inline uint32_t tile_to_chunk_index(Coord c) { coord_to_index(tile_to_chunk(c)); }

   inline Coord get_chunk_left_corner_tile(Coord chunk)
   {
	return {chunk.x * CHUNK_LENGTH, chunk.y * CHUNK_LENGTH};
   }

   // OPTI
   inline Coord get_chunk_left_corner_tile(uint16_t chunk_index)
   {
	return {get_chunk_left_corner_tile(chunk_index_to_chunk(chunk_index))};
   }

   inline SDL_Point tile_to_chunk_relative_point(Coord coord)
   {
     return {static_cast<int>(coord.x % CHUNK_LENGTH), static_cast<int>(coord.y % CHUNK_LENGTH)};
   }

  inline std::vector<uint16_t> get_chunks_from_area(Rect area)
{
	uint16_t chunk_amount =
	    ((area.h / CHUNK_LENGTH) + 1) * ((area.w / CHUNK_LENGTH) + 1);
	std::vector<uint16_t> chunks(chunk_amount);
	uint16_t index = 0;
	for (uint16_t i = area.x / CHUNK_LENGTH; i < (area.x + area.w / CHUNK_LENGTH) + 1; i++)
	{
		for (uint16_t j = area.y / CHUNK_LENGTH; j < (area.y + area.y / CHUNK_LENGTH) + 1; j++)
		{
			chunks[index++] = (j * j) + i;
		}
	}
	return chunks;
}

void move(Coord& coord, Direction direction)
{
        switch (direction) {
        case Direction::North:
       	  coord.y += 1;
       	  break;
        case Direction::South:
       	  coord.y -= 1;
	  break;
        case Direction::East:
       	  coord.x += 1;
       	  break;
        default:
          coord.x -= 1;
        }
   assert(!out_of_bounds(coord));
}  

  bool coords_in_path(Coord start, Coord end, Coord between)
{
        assert(!out_of_bounds(start) && !out_of_bounds(end) && !out_of_bounds(between));

	uint32_t dx = unsigned_abs_diff(end.x , start.x);
	uint32_t dy = unsigned_abs_diff(end.y , start.y);
	uint32_t sx = start.x < end.x ? 1 : -1;
	uint32_t sy = start.y < end.y ? 1 : -1;
	uint32_t err = dx - dy;

	uint32_t x = start.x;
	uint32_t y = start.y;

	while (true)
	{
		if (y == between.y && x == between.x)
		{
			return true;
		}

		if (x == end.x && y == end.y)
		{
			break; 
		}

		uint32_t e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}

	return false;
}  
}
  

  
