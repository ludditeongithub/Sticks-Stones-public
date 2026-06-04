#pragma once
#include "animation.hpp"
#include "core/data.hpp"
#include "screen.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "viewport.hpp"
#include "sprite_sheet_settings.hpp"
#include <core/entity.hpp>
#include <core/packed_enum.hpp>
#include <core/tables.hpp>
#include <cstdint>
#include <systems/find_nearest.hpp>
#include <systems/perishables_manager.hpp>
#include <world/animal/enum.hpp>
#include <world/item/entity.hpp>
#include <world/plant/enum.hpp>
#include <world/tile/data.hpp>
#include <world/tile/enum.hpp>

constexpr uint16_t RENDER_CHUNK_WIDTH = 4;
constexpr uint16_t RENDER_CHUNK_HEIGHT = 4;

// entities are stored by central tile, but must drawn from left corner tile
inline Coord getLeftCornerTile(Coord origin, Coord dimensions)
{
	return {origin.x - (dimensions.x / 2), origin.y - dimensions.y};
}

inline void copyTiles(SDL_Texture* chunkTexture, World& world, Array<TileData> &tiles)
{
	for (uint16_t i = 0; i < SCREEN_TILE_HEIGHT; i++)
	{
		for (uint16_t j = 0; j < SCREEN_TILE_WIDTH; j++)
		{
			uint16_t ti = world.getTileIndexFromCoord({i, j});
			// draw tiles
			Tile t = tiles[ti].first();
			SDL_Rect sd = SpriteSheet::tileSprites[static_cast<int>(t)];
			spriteSheetTexture.render(j * TILE_LENGTH, i * TILE_LENGTH, &sd,
						   &mainScreenViewport);

			// draw grass
			Grass g = tiles[ti].second();
			if (g != Grass::NONE)
			{
				sd = SpriteSheet::grassSprites[static_cast<int>(g)];
				spriteSheetTexture.render(i * TILE_LENGTH, j * TILE_LENGTH, &sd, &mainScreenViewport);
		}
	}
	}
}	

void copyPlants(EntityRenderBuffer &erd)
{
	for (uint16_t i = 0; i < erd.plantAmount; i++)
	{
		EntitySearchData esd = {erd.plants[i].index, erd.plants[i].position};
		
		SDL_Rect sr = plantSpriteDimensions[erd.plants[i].plant];
		Coord lc = getLeftCornerTile(
		    esd.position, {static_cast<uint32_t>(sr.w), static_cast<uint32_t>(sr.y)});
		spriteSheetTexture.render(lc.x, lc.y, &sr, &mainScreenViewport);
	}
}

void copyItems(EntityRenderBuffer &erd)
{
	for (uint16_t i = 0; i < erd.itemAmount; i++)
	{
		EntitySearchData esd = {erd.items[i].index, erd.plants[i].position};
		SDL_Rect sr = itemSpriteDimensions[erd.items[i].item];
		Coord lc = getLeftCornerTile(
		    esd.position, {static_cast<uint32_t>(sr.w), static_cast<uint32_t>(sr.y)});
		spriteSheetTexture.render(lc.x, lc.y, &sr, &mainScreenViewport);
	}
}

//renders entites which can't be chunked
void renderMovingEntities(World& world, Coord leftCorner, Array<TileData> &tiles, Array<Time> &animalAges,
		  Array<Frame> &animalFrames, Array<AnimalStatus> &animalStates,
		  Array<FrameData>& unitFrameData, Array<Time> &unitAges,
		  SearchGrid &sg, EntityRenderBuffer& entityRenderBuffer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	updateAnimalAnimations(leftCorner, entityRenderBuffer, animalFrames, animalAges, animalStates);

	updateUnitAnimations(leftCorner, entityRenderBuffer, unitAges, unitFrameData);

	// draw equippables

	// draw alternate items

	//TODO: upscale

	// update screen
	SDL_RenderPresent(renderer);
}
  
SDL_Texture& renderChunkTexture(World& world, Array<TileData>& tiles, Coord leftCorner, EntityRenderBuffer& entityRenderBuffer)
{
	SDL_Texture *chunkTexture =
	    SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			      RENDER_CHUNK_WIDTH, RENDER_CHUNK_HEIGHT);
	
	SDL_SetRenderTarget(renderer, chunkTexture);

	copyTiles(chunkTexture, world, tiles);
	copyItems(entityRenderBuffer);
	copyPlants(entityRenderBuffer);
}	

