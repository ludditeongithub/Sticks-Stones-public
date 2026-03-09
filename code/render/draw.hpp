#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <core/entity.hpp>
#include <core/packed_enum.hpp>
#include <systems/perishables_manager.hpp>
#include <world/item/enum.hpp>
#include <cstdint>
#include <variant>
#include "core/data.hpp"
#include "screen.hpp"
#include "texture.hpp"
#include "animation.hpp"
#include "viewport.hpp"
#include <world/tile/enum.hpp>
#include <world/tile/data.hpp>
#include <world/plant/enum.hpp>
#include <world/animal/enum.hpp>
#include <systems/find_nearest.hpp>

using Sprite = std::variant<Item, Wearable, Vehicle, Container, Animal, Plant, Unit>;
    /*    item 9
        wearable 3
        vehicle 5
        container 4
        animal 6
        Plant 6
	unit 3
    */

inline constexpr LookupTable<Tile, Coord> tileSpriteLocations = [] {
  LookupTable<Tile,Coord> lt{};
  using enum Tile;
  
  return lt;
}();

inline constexpr LookupTable<Grass,Coord> grassSpriteLocations = [] {
  LookupTable<Grass,Coord> lt{};
  using enum Grass;
  
  return lt;
 }();

// since the base tile is the one that matters the most, dimensions are always IN REVERSE when it comes to the y coordinate
inline constexpr LookupTable<Item, SDL_Rect> itemSpriteDimensions = [] {
  LookupTable<Item,SDL_Rect> lt{};
  using enum Item;
  
  return lt;
}();

inline constexpr LookupTable<Wearable, SDL_Rect>
    wearableSpriteDimensions = [] {
      LookupTable<Wearable, SDL_Rect> lt{};
      using enum Wearable;

      return lt;
    }();

inline constexpr LookupTable<Animal, SDL_Rect> animalSpriteDimensions =
    [] {
      LookupTable<Animal, SDL_Rect> lt{};
      using enum Animal;

      return lt;
    }();

inline constexpr LookupTable<Plant, SDL_Rect> plantSpriteDimensions = [] {
  LookupTable<Plant ,SDL_Rect> lt{};
  using enum Plant ;
  
  return lt;
}();

inline constexpr LookupTable<Vehicle, SDL_Rect> vehicleSpriteDimensions =
    [] {
      LookupTable<Vehicle, SDL_Rect> lt{};
      using enum Vehicle;

      return lt;
    }();

inline constexpr LookupTable<Container, SDL_Rect>
    containerSpriteDimensions = [] {
      LookupTable<Container, SDL_Rect> lt{};
      using enum Container;

      return lt;
    }();

inline constexpr LookupTable<Unit, SDL_Rect> unitSpriteDimensions = [] {
  LookupTable<Unit,SDL_Rect> lt{};
  using enum Unit;
  
  return lt;
}();

// entities are stored by central tile, but must drawn from left corner tile
inline Coord getLeftCornerTile(Coord origin, Coord dimensions) {
  return {origin.x - (dimensions.x/2), origin.y - dimensions.y};
}

SDL_Rect getSDLRect(const Sprite& sprite) {
  if (const Item* item = std::get_if<Item>(&sprite)) {
    return itemSpriteDimensions[*item];
  }else if (const Plant* plant = std::get_if<Plant>(&sprite)) {
    return plantSpriteDimensions[*plant];
  } else if (const Wearable* wearable = std::get_if<Wearable>(&sprite)) {
    return wearableSpriteDimensions[*wearable];
  } else if (const Unit* unit = std::get_if<Unit>(&sprite)) {
    return unitSpriteDimensions[*unit];
  } else if (const Animal* animal = std::get_if<Animal>(&sprite)) {
    return animalSpriteDimensions[*animal];
  } else if (const Vehicle* vehicle = std::get_if<Vehicle>(&sprite)) {
    return vehicleSpriteDimensions[*vehicle];
  } else if (const Container* container = std::get_if<Container>(&sprite)) {
    return containerSpriteDimensions[*container];
  }
}

void drawPlants(EntityRenderBuffer& erd) {
   for (uint16_t i = 0; i < erd.plantAmount; i++) {
    EntitySearchData esd = erd.plants[i];
    SDL_Rect sr = plantSpriteDimensions[erd.plants[esd.index]];    
    Coord lc = getLeftCornerTile(esd.position, {static_cast<uint32_t>(sr.w), static_cast<uint32_t>(sr.y)});
    gSpriteSheetTexture.render(lc.x, lc.y, &sr, &mainScreenViewport);
  }
}

void drawItems(EntityRenderBuffer& erd) {
	for (uint16_t i = 0; i < erd.itemAmount; i++) {
    EntitySearchData esd = erd.items[i];
    SDL_Rect sr = itemSpriteDimensions[erd.items[esd.index]];    
    Coord lc = getLeftCornerTile(esd.position, {static_cast<uint32_t>(sr.w), static_cast<uint32_t>(sr.y)});
    gSpriteSheetTexture.render(lc.x, lc.y, &sr, &mainScreenViewport);
  }
}

void drawEntities(Coord leftCorner, Array<TileData>& tiles, Array<Time>& animalAges, Array<Frame>& animalFrames, Array<AnimalStatus> &animalStates, Array<Frame> &unitFrames, Array<Time>& unitAges, Array<ActState>& unitStates, 
		SearchGrid& sg) {
  //Clear screen
  SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_RenderClear(gRenderer);
  
  for (uint16_t i = leftCorner.y; i < leftCorner.y + SCREEN_TILE_HEIGHT; i++) {
    for (uint16_t j = leftCorner.x; j < leftCorner.x + SCREEN_TILE_WIDTH; j++) {
      uint16_t ti = getTileIndexFromCoord({i, j});
      // draw tiles      
      Tile t = tiles[ti].first();
      Coord c = tileSpriteLocations[t];
      SDL_Rect sd = {static_cast<int>(c.x), static_cast<int>(c.y), 1, 1};
      gSpriteSheetTexture.render(j * TILE_LENGTH, i * TILE_LENGTH, &sd, &mainScreenViewport);
      
      // draw grass
      Grass g = tiles[ti].second();
      c = grassSpriteLocations[g];
      sd =  {static_cast<int>(c.x), static_cast<int>(c.y), 1, 1};
      gSpriteSheetTexture.render(i * TILE_LENGTH, j * TILE_LENGTH, &sd, &mainScreenViewport);
    }
  }
  EntityRenderBuffer erd =
      sg.getAllInRange(leftCorner, {SCREEN_TILE_WIDTH, SCREEN_TILE_HEIGHT});

  // draw plants
  drawPlants(erd);

  // draw items
  drawItems(erd);
  
  // draw animals
  updateAnimalAnimations(leftCorner, erd, animalFrames, animalAges, animalStates);

  // draw units
  updateUnitAnimations(leftCorner, erd, unitFrames, unitAges, unitStates);
			 
  // draw equippables
  

  // draw alternate items
  
  //update screen
  SDL_RenderPresent( gRenderer );
}

#endif
