#pragma once
#include <core/coord.hpp>
#include "data/const/chunk_data.hpp"
#include <SDL2/SDL_render.h>
#include <SDL_rect.h>
#include <core/containers.hpp>
#include <logic/simulation/game.hpp>
#include <core/packed_enum.hpp>
#include <data/run/coord.hpp>
#include <core/tables.hpp>
#include <cstdint>
#include <data/types/animal.hpp>
#include <data/run/item_database.hpp>
#include <data/types/plant.hpp>
#include <data/const/tile_data.hpp>
#include <data/types/tile.hpp>
#include <data/const/plant_tables.hpp>
#include <display/render/sprite.hpp>
#include <data/types/rendering.hpp>
#include <data/run/plant_database.hpp>
#include <data/game/screen.hpp>
#include <data/run/texture.hpp>
#include <data/run/camera.hpp>
#include <logic/generic/search/search.hpp>

// entities are stored by central tile, but must drawn from left corner tile
inline Coord get_left_corner_tile(Coord origin, Coord dimensions)
{
	return {origin.x - (dimensions.x / 2), origin.y - dimensions.y};
}

void render_tiles_in_chunk(uint16_t chunk, Array<TileData> &tiles)
{
	for (uint16_t i = 0; i < SCREEN_TILE_HEIGHT; i++)
	{
		for (uint16_t j = 0; j < SCREEN_TILE_WIDTH; j++)
		{
		  uint32_t ti = coord_to_index(Coord{i, j});
		  
			Tile t = tiles[ti].get<Tile>();
			SDL_Rect sd = sprite::tiles[t];
		        SDL_Rect ds = make_sdl_rect(i * TILE_LENGTH, j * TILE_LENGTH, TILE_LENGTH, TILE_LENGTH);
		        chunk_texture::render(chunk, &sd, &ds);

			Grass g = tiles[ti].get<Grass>();
			if (g != Grass::NONE)
			{
			  sd = sprite::grasses[g];
			  SDL_Rect ds = make_sdl_rect(i * TILE_LENGTH, j * TILE_LENGTH, TILE_LENGTH, TILE_LENGTH);
			  chunk_texture::render(chunk, &sd, &ds);
		}
	}
	}
}

// TODO: for copy_plants and items, change the search grid algo to return coord relative to chunk instead of absolute coord
// TODO: DEBUG: ensure consistency here for which corner is left corner, which corner is the actual location of the plant for plants of even dimensions. also ensure that the dimensions passed to get_left_corner_tile are in tiles note pixels
void render_plants_in_chunk(uint16_t chunk, ChunkRenderBuffer &erd, plant::Database& pdb)
{
	for (uint16_t i = 0; i < erd.plant_amount; i++)
	{
	  const PlantRenderData pr = erd.plants[i];
	  // TODO: should be based on growth rather than age
		float age_ratio = std::min((float)1.0, pdb.age(pr.index) / FULL_MATURITY_AGES[pr.plant]);
		int stage = age_ratio * sprite::PLANT_STAGE_AMOUNTS[pr.plant];
		SDL_Rect sr = sprite::get_plant(pr.plant, stage);
		Coord lc = get_left_corner_tile(
		                    pr.position, {static_cast<uint32_t>(sr.w), static_cast<uint32_t>(sr.h)});
	        SDL_Point p = coord::tile_to_chunk_relative_point(lc);
	        SDL_Rect ds{p.x, p.y, sr.w, sr.h};
                chunk_texture::render(chunk, &sr, &ds);
	}
}

void render_chunked_items(uint16_t chunk, ChunkRenderBuffer &erd)
{
	for (uint16_t i = 0; i < erd.item_amount; i++)
	{
		EntitySearchData esd = {erd.items[i].index, erd.plants[i].position};
                //  Coord c = sprite::ITEM_DIMENSIONS[erd.items[i].item];
                SDL_Rect sr = sprite::items[erd.items[i].item];
		Coord lc =
		    get_left_corner_tile(esd.position.value(), {static_cast<uint32_t>(sr.w),
								static_cast<uint32_t>(sr.y)});
	        SDL_Point p = coord::tile_to_chunk_relative_point(lc);
	        SDL_Rect ds{p.x, p.y, sr.w, sr.h};
	        chunk_texture::render(chunk, &sr, &ds);
	}
}

// TODO: render_chunked_buildables

constexpr uint16_t RENDER_CHUNK_WIDTH = 4;
constexpr uint16_t RENDER_CHUNK_HEIGHT = 4;

// chunks update lazily
void update_and_render_chunk_textures(std::vector<uint16_t>& chunks_in_area, Array<TileData>& tile_datas, plant::Database& plants)
{      
	SDL_RenderSetViewport(renderer, g_chunk_texture_viewport);
	for (auto i : chunks_in_area)
	  {
		  if (!chunk_texture::updated[i])
		    {
		      // update chunk texture   
	ChunkRenderBuffer entity_render_buffer =
	  g_search->get_non_movables_in_chunk(i);
	              // OPTI: instead of updated[i], enum which details exactly what was changed for minimum render change
	render_tiles_in_chunk(i, tile_datas);
	render_chunked_items(i, entity_render_buffer);
	render_plants_in_chunk(i, entity_render_buffer, plants);
		    }
	  }

  SDL_RenderSetViewport(renderer, g_main_screen_viewport);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  
	SDL_SetRenderTarget(renderer, nullptr); //nullptr for screen
	for (auto i : chunks_in_area)
	  {
	    Coord lc = coord::get_chunk_left_corner_tile(i);
	    SDL_RenderCopy(
		renderer, chunk_texture::textures[i], nullptr,
		{static_cast<int>(lc.x), static_cast<int>(lc.y), CHUNK_LENGTH, CHUNK_LENGTH});
	  }        
}

// TODO: pre-render a bit wider then camera
void render_chunks_in_view()
{  
  std::vector<uint16_t> acs = coord::get_chunks_from_area(g_camera);
  update_and_render_chunk_textures(acs, g_game->tile_database.tileDatas, g_game->plant_database);  
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
