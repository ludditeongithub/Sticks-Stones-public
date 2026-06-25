#pragma once
#include <extern/json.hpp>
#include <fstream>
#include "sprite.hpp"
#include "sprite_names.hpp"
#include <SDL2/SDL_rect.h>
#include <world/animal/enum.hpp>
#include <world/item/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/buildable/enum.hpp>
#include <world/tile/enum.hpp>
#include <ui/components/button.hpp>
#include <variant>

namespace SpriteSheet
{
using json = nlohmann::json;
// using Sprite = std::variant<Item, Plant, Tile, Grass, Animal, Unit, Buildable, ButtonSprite, UISprite>;

std::array<SDL_Rect, static_cast<size_t>(Animal::MAX)> animalSprites;
std::array<SDL_Rect, static_cast<size_t>(Buildable::MAX)> buildableSprites;
std::array<SDL_Rect, static_cast<size_t>(Plant::MAX)> plantSprites;
std::array<SDL_Rect, static_cast<size_t>(Item::MAX)> itemSprites;
std::array<SDL_Rect, static_cast<size_t>(Tile::MAX)> tileSprites;
std::array<SDL_Rect, static_cast<size_t>(Grass::MAX)> grassSprites;
std::array<SDL_Rect, static_cast<size_t>(ButtonSprite::MAX)> buttonSprites;
std::array<SDL_Rect, static_cast<size_t>(UISprite::MAX)> UISprites;

template<typename Sprite>
inline void saveSprite(int index, Sprite sprite, SCoord position, SCoord dimension)
{
	if (std::is_same<Animal, Sprite>::value) {
		animalSprites[index] = SDL_Rect{position.x, position.y, dimension.x, dimension.y};	
	    } else if (std::is_same<Buildable, Sprite>::value) {
		buildableSprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Plant, Sprite>::value) {
		plantSprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Item, Sprite>::value) {
		itemSprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Tile, Sprite>::value) {
		tileSprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Grass, Sprite>::value) {
		grassSprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<ButtonUI, Sprite>::value) {
          buttonSprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y}; // NOTE: since buttons have three states, the dimension is divided by 3.
	} else if (std::is_same<UISprite, Sprite>::value ) {
		UISprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} 
}

// TODO: fix using BetterEnum
template <typename Enum>
void loadOneTypeSprites(const json& sheet) {
    for (size_t i = 0; i < static_cast<size_t>(Enum::MAX); i++) {
        Enum sprite = static_cast<Enum>(i);

        SCoord positions{}, dimensions{};

        for (const auto& item : sheet) {
            if (item.contains("filename") &&
                item["filename"] == getSpriteName(sprite)) { 

                positions = {item["frame"]["x"], item["frame"]["y"]};
                dimensions = {item["frame"]["w"], item["frame"]["h"]};
            }
        }

        saveSprite(i, sprite, positions, dimensions);
    }
}

template <typename ... Enums>
void loadTypeSprites() {
	std::ifstream file("../../sprites/game.json");

	json sheet;
	file >> sheet;
	(loadOneTypeSprites<Enums>(sheet), ...);
}

void loadSprites()
{
	loadTypeSprites<Animal, Plant, Item, Tile, Grass, Buildable,  ButtonSprite, UISprite>();
}	

};

