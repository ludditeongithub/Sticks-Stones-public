#pragma once
#include "animation.hpp"
#include "core/data.hpp"
#include "screen.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "sprite_sheet_settings.hpp"
#include <SDL2/SDL_render.h>
#include <core/containers.hpp>
#include <core/packed_enum.hpp>
#include <core/tables.hpp>
#include <cstdint>
#include <world/animal/enum.hpp>
#include <world/item/database.hpp>
#include <world/plant/enum.hpp>
#include <world/tile/data.hpp>
#include <world/tile/enum.hpp>

constexpr uint16_t RENDER_CHUNK_WIDTH = 4;
constexpr uint16_t RENDER_CHUNK_HEIGHT = 4;

// entities are stored by central tile, but must drawn from left corner tile
inline Coord get_left_corner_tile(Coord origin, Coord dimensions)
{
	return {origin.x - (dimensions.x / 2), origin.y - dimensions.y};
}

inline void copy_tiles(SDL_Texture* chunk_texture, World& world, Array<TileData> &tiles)
{
	for (uint16_t i = 0; i < SCREEN_TILE_HEIGHT; i++)
	{
		for (uint16_t j = 0; j < SCREEN_TILE_WIDTH; j++)
		{
			uint16_t ti = world.get_tile_index_from_coord({i, j});
			// draw tiles
			Tile t = tiles[ti].first();
			SDL_Rect sd = sprite::tile[static_cast<int>(t)];
			sprite_sheet_texture.render(j * TILE_LENGTH, i * TILE_LENGTH, &sd,
						   &main_screen_viewport);

			// draw grass
			Grass g = tiles[ti].second();
			if (g != Grass::NONE)
			{
				sd = SpriteSheet::grass[static_cast<int>(g)];
				sprite_sheet_texture.render(i * TILE_LENGTH, j * TILE_LENGTH, &sd, &main_screen_viewport);
		}
	}
	}
}	

void copy_plants(EntityRenderBuffer &erd)
{
	for (uint16_t i = 0; i < erd.plant_amount; i++)
	{
		EntitySearchData esd = {erd.plants[i].index, erd.plants[i].position};
		
		SDL_Rect sr = plant_sprite_dimensions[erd.plants[i].plant];
		Coord lc = get_left_corner_tile(
		    esd.position, {static_cast<uint32_t>(sr.w), static_cast<uint32_t>(sr.y)});
		sprite_sheet_texture.render(lc.x, lc.y, &sr, &main_screen_viewport);
	}
}

void copy_items(EntityRenderBuffer &erd)
{
	for (uint16_t i = 0; i < erd.item_amount; i++)
	{
		EntitySearchData esd = {erd.items[i].index, erd.plants[i].position};
		SDL_Rect sr = item_sprite_dimensions[erd.items[i].item];
		Coord lc = get_left_corner_tile(
		    esd.position, {static_cast<uint32_t>(sr.w), static_cast<uint32_t>(sr.y)});
		sprite_sheet_texture.render(lc.x, lc.y, &sr, &main_screen_viewport);
	}
}

//renders entites which can't be chunked
void render_moving_entities(World& world, Coord left_corner, Array<TileData> &tiles, Array<Time> &animal_ages,
		  Array<Frame> &animal_frames, Array<AnimalStatus> &animal_states,
		  Array<FrameData>& unit_frame_data, Array<Time> &unit_ages,
		  SearchGrid &sg, EntityRenderBuffer& entity_render_buffer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	update_animal_animations(left_corner, entity_render_buffer, animal_frames, animal_ages, animal_states);

	update_unit_animations(left_corner, entity_render_buffer, unit_ages, unit_frame_data);

	// draw equippables

	// draw alternate items

	//TODO: upscale

	// update screen
	SDL_RenderPresent(renderer);
}
  
SDL_Texture& render_chunk_texture(World& world, Array<TileData>& tiles, Coord left_corner, EntityRenderBuffer& entity_render_buffer)
{
	SDL_Texture *chunk_texture =
	    SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			      RENDER_CHUNK_WIDTH, RENDER_CHUNK_HEIGHT);
	
	SDL_SetRenderTarget(renderer, chunk_texture);

	copy_tiles(chunk_texture, world, tiles);
	copy_items(entity_render_buffer);
	copy_plants(entity_render_buffer);
}

enum class Renderable
{
	Tile,
	Grass,
	Animal,
	Plant,
	Unit,
	Buildable
};

enum class RenderChange
{
	Replacement,
	MovementUp,
	MovementDown,
	MovementLeft,
	MovementRight
};

struct RenderingEvent
{
	Renderable renderable;
	uint32_t index;
	
};

struct RenderingEventsBuffer { //events that have taken place since last render, which will require certain chunks to be re-rendered
	
};

struct RenderManager
{
	bool first_render = false;
	
	void render(World& world, Array<TileData>& tiles, RenderingEventsBuffer& rendering_events_buffer)
	{
		EntityRenderBuffer entity_render_buffer;
		if (first_render)
		{
	// render rendering-chunks
	for (size_t i = 0; i < world.world_tile_length; i+=RENDER_CHUNK_WIDTH) {
		for (size_t j = 0; j < world.world_tile_length; j+=RENDER_CHUNK_HEIGHT) {
			render_chunk_texture(world, tiles, {i,j} , entity_render_buffer);
		}
	}
		} else {			
		  
	}
	
}	

};

