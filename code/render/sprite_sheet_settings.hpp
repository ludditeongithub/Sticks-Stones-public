#pragma once
#include <json.hpp>
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

namespace sprite
{
using json = nlohmann::json;
// using Sprite = std::variant<Item, Plant, Tile, Grass, Animal, Unit, Buildable, ButtonSprite, UISprite>;

std::array<SDL_Rect, static_cast<size_t>(Animal::MAX)> animal_sprites;
std::array<SDL_Rect, static_cast<size_t>(Buildable::MAX)> buildable;
std::array<SDL_Rect, static_cast<size_t>(Plant::MAX)> plant_sprites;
std::array<SDL_Rect, static_cast<size_t>(Item::MAX)> item_sprites;
std::array<SDL_Rect, static_cast<size_t>(Tile::MAX)> tile_sprites;
std::array<SDL_Rect, static_cast<size_t>(Grass::MAX)> grass_sprites;
std::array<SDL_Rect, static_cast<size_t>(Unit::MAX)> unit_sprites;
std::array<SDL_Rect, static_cast<size_t>(ButtonSprite::MAX)> button_sprites;
std::array<SDL_Rect, static_cast<size_t>(UISprite::MAX)> ui_sprites;

template<typename Sprite>
inline void save_sprite(int index, Sprite sprite, SCoord position, SCoord dimension)
{
	if (std::is_same<Animal, Sprite>::value) {
		animal_sprites[index] = SDL_Rect{position.x, position.y, dimension.x, dimension.y};	
	    } else if (std::is_same<Buildable, Sprite>::value) {
		buildable[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Plant, Sprite>::value) {
		plant_sprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Item, Sprite>::value) {
		item_sprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Tile, Sprite>::value) {
		tile_sprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Grass, Sprite>::value) {
		grass_sprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<ButtonUI, Sprite>::value) {
          button_sprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y}; // NOTE: since buttons have three states, the dimension is divided by 3.
	} else if (std::is_same<UISprite, Sprite>::value ) {
		ui_sprites[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} 
}

// TODO: fix using BetterEnum
template <typename Enum>
void load_one_type_sprites(const json& sheet) {
    for (size_t i = 0; i < static_cast<size_t>(Enum::MAX); i++) {
        Enum sprite = static_cast<Enum>(i);

        SCoord positions{}, dimensions{};

        for (const auto& item : sheet) {
            if (item.contains("filename") &&
                item["filename"] == get_sprite_name(sprite)) { 

                positions = {item["frame"]["x"], item["frame"]["y"]};
                dimensions = {item["frame"]["w"], item["frame"]["h"]};
            }
        }

        save_sprite(i, sprite, positions, dimensions);
    }
}

template <typename ... Enums>
void load_type_sprites() {
	std::ifstream file("../../sprites/game.json");

	json sheet;
	file >> sheet;
	(load_one_type_sprites<Enums>(sheet), ...);
}

void load_sprites()
{
	load_type_sprites<Animal, Plant, Item, Tile, Grass, Buildable,  ButtonSprite, UISprite>();
}	

};

