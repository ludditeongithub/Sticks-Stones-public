#pragma once
#include "data/const/unit_data.hpp"
#include "data/run/plant_database.hpp"
#include "data/types/entity.hpp"
#include "display/render/sprite.hpp"
#include "texture.hpp"
#include <SDL2/SDL_render.h>
#include <core/containers.hpp>
#include <core/packed_enum.hpp>
#include <core/tables.hpp>
#include <cstdint>
#include <cmath>
#include <data/types/animal.hpp>
#include <data/run/item_database.hpp>
#include <data/types/plant.hpp>
#include <data/const/tile_data.hpp>
#include <data/types/tile.hpp>
#include <data/const/plant_tables.hpp>
#include <display/render/render_chunk.hpp>

// entities are stored by central tile, but must drawn from left corner tile
inline Coord get_left_corner_tile(Coord origin, Coord dimensions)
{
	return {origin.x - (dimensions.x / 2), origin.y - dimensions.y};
}

inline void copy_tiles(World& world, Array<TileData> &tiles)
{
	for (uint16_t i = 0; i < SCREEN_TILE_HEIGHT; i++)
	{
		for (uint16_t j = 0; j < SCREEN_TILE_WIDTH; j++)
		{
			uint16_t ti = world.get_tile_index_from_coord({i, j});
			// draw tiles
			Tile t = tiles[ti].get<Tile>();
			SDL_Rect sd = sprite::tiles[t];
			sprite_sheet_texture.render(j * TILE_LENGTH, i * TILE_LENGTH, &sd,
						   &main_screen_viewport);

			// draw grass
			Grass g = tiles[ti].get<Grass>();
			if (g != Grass::NONE)
			{
				sd = sprite::grasses[g];
				sprite_sheet_texture.render(i * TILE_LENGTH, j * TILE_LENGTH, &sd, &main_screen_viewport);
		}
	}
	}
}	

void copy_plants(EntityRenderBuffer &erd, plant::Database& pdb)
{
	for (uint16_t i = 0; i < erd.plant_amount; i++)
			{
		const PlantRenderData pr = erd.plants[i];
		const std::array<sprite::StageInfo, sprite::MAX_STAGES> &sd = sprite::PLANT_SPRITE_DIMENSIONS[erd.plants[i].plant];
                
		float age_ratio = std::min(1.0, pdb.age(pr.index) / FULL_MATURITY_AGES[pr.plant]);
		int stage = age_ratio * sprite::PLANT_STAGE_AMOUNTS[pr.plant];
		SDL_Rect sr = sprite::PLANT_SPRITE_DIMENSIONS[pr.plant];
					
		Coord lc = get_left_corner_tile(
		    pr.position, {static_cast<uint32_t>(sr.w), static_cast<uint32_t>(sr.y)});
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

//TODO: right now not rendered as texture
SDL_Texture& render_chunk_texture(World& world, Array<TileData>& tiles, Coord left_corner, EntityRenderBuffer& entity_render_buffer, plant::Database& plants)
{
	SDL_Texture *chunk_texture =
	    SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, RENDER_CHUNK_WIDTH, RENDER_CHUNK_HEIGHT);
	
	SDL_SetRenderTarget(renderer, chunk_texture);

	copy_tiles(world, tiles);
	copy_items(entity_render_buffer);
	copy_plants(entity_render_buffer, plants);
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
