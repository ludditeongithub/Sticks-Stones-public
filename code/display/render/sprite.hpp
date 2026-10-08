// Stores hot arrays of sprite data (positions, sizes, colors, texture IDs), handles batching logic
#pragma once
#include "core/tables.hpp"
#include <SDL_rect.h>
#include <data/types/item.hpp>
#include <data/types/buildable.hpp>
#include <data/types/animal.hpp>
#include <data/types/plant.hpp>
#include <data/types/unit.hpp>
#include <data/types/tile.hpp>
#include <data/types/entity.hpp>
#include <data/types/ui.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <json.hpp>
#include <filesystem>
#include <magic_enum/magic_enum.hpp>

// TODO: right now this is only fitted for walk animations. need to make sure
// all the LOGIC is only fitted for walk animations, for now.
using json = nlohmann::json;

namespace sprite
{

// using Sprite = std::variant<Item, Plant, Tile, Grass, Animal, Unit, Buildable, ButtonSprite, UISprite>;

  RuntimeLookupTable<Animal, SDL_Rect> animals;

  RuntimeLookupTable<Buildable, SDL_Rect> buildables;

  RuntimeLookupTable<Plant,SDL_Rect> plants;

  RuntimeLookupTable<Item,SDL_Rect> items;

  RuntimeLookupTable<Tile,SDL_Rect> tiles;

  RuntimeLookupTable<Grass,SDL_Rect> grasses;

  RuntimeLookupTable<Unit,SDL_Rect> units;

  RuntimeLookupTable<ButtonSprite,SDL_Rect> buttons;

  RuntimeLookupTable<CustomButtonDecoration,SDL_Rect> custom_decorations;

  RuntimeLookupTable<UISprite,SDL_Rect> uis;

  RuntimeLookupTable<Role, SDL_Rect> roles;

  SDL_Rect null_sprite;	


std::string to_kebab_case(std::string& s) {
    std::string result;

    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];

        if (std::isupper(static_cast<unsigned char>(c))) {
            if (i > 0) result += '-';
            result += std::tolower(static_cast<unsigned char>(c));
        } else {
            result += c;
        }
    }

    return result;
}

template<typename S>
std::string get_sprite_name(S sprite_type)
{
		std::string name = std::string(magic_enum::enum_name(sprite_type));

    if constexpr (std::is_same_v<S, Plant>)
    {
        if (auto item = magic_enum::enum_cast<Item>(name); item.has_value())
        {
            name += "-plant";
        }
    }
    return to_kebab_case(name) + ".aseprite";
}
  
template<typename Sprite>
inline void save_sprite(int index, Sprite sprite, SCoord position, SCoord dimension)
{
	if (std::is_same<Animal, Sprite>::value) {
		animals[static_cast<Animal>(index)] = SDL_Rect{position.x, position.y, dimension.x, dimension.y};	
        } else if (std::is_same<Buildable, Sprite>::value) {
		buildables[static_cast<Buildable>(index)] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Plant, Sprite>::value) {
		plants[static_cast<Plant>(index)] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Item, Sprite>::value) {
		items[static_cast<Item>(index)] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Tile, Sprite>::value) {
		tiles[static_cast<Tile>(index)] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Grass, Sprite>::value) {
		grasses[static_cast<Grass>(index)] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<ButtonSprite, Sprite>::value) {
          buttons[static_cast<ButtonSprite>(index)] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y}; // NOTE: since buttons have three states, the dimension is divided by 3.
	} else if (std::is_same<UISprite, Sprite>::value) {
		uis[static_cast<UISprite>(index)] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	}
	else if (std::is_same<Role, Sprite>::value) {
                roles[static_cast<Role>(index) ] = SDL_Rect{position.x, position.y, dimension.x, dimension.y};
        } else if (std::is_same<CustomButtonDecoration, Sprite>::value) {          custom_decorations[static_cast<CustomButtonDecoration>(index) ] = SDL_Rect{position.x, position.y, dimension.x, dimension.y};
        } else throw std::invalid_argument("Invalid Sprite type.");
}

template <typename Enum> void load_one_type_sprites(const json &sheet)
{
	std::cout << "Started loading one type sprite.";
	
    for (size_t i = 0; i < static_cast<size_t>(Enum::MAX); i++) {
        Enum sprite = static_cast<Enum>(i);
		
        SCoord positions{}, dimensions{};

	for (auto &item : sheet)
			{
					std::string s = item["filename"].get<std::string>();
					std::cout << "sprite name:" + s + '\n';
					std::string sn = get_sprite_name(sprite);
				if (s == sn)
				{						
						std::cout << "Loaded sprite: " + get_sprite_name(sprite);
					
					positions = {item["frame"]["x"], item["frame"]["y"]};
                dimensions = {item["frame"]["w"], item["frame"]["h"]};
            }
        }

        save_sprite(i, sprite, positions, dimensions);
    }
}

template <typename... Enums> void load_type_sprites()
{
	std::cout << std::filesystem::current_path() << '\n';

	std::string file_name = "../../assets/sprites/game.json";
    std::ifstream file(file_name, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Failed to open: " << file_name << '\n';
        return;
    }

    std::cout << "Successfully opened: " << file_name << '\n';

    json sheet = json::parse(file);

    (load_one_type_sprites<Enums>(sheet), ...);
}

void load_sprites()
{
	load_type_sprites<Animal, Plant, Item, Tile, Grass, Buildable,  ButtonSprite, UISprite>();
}	

SDL_Rect get(Entity entity)
{
  if (auto x = std::get_if<Item>(&entity)) {
    return items[*x];
  } else if (auto x = std::get_if<Plant>(&entity)) {
    return plants[static_cast<Plant>(*x) ];
  } else if (auto x = std::get_if<Animal>(&entity)) {
    return animals[static_cast<Animal>(*x) ];
  } else if (auto x = std::get_if<Buildable>(&entity)) {
    return buildables[static_cast<Buildable>(*x) ];
  } else if (auto x = std::get_if<Unit>(&entity)) {
    return units[*x];
  } else { // NullEntity
    // TODO: throw error
  }
}

  inline SDL_Rect get_button(ButtonSprite sprite, ButtonState state)
{
   SDL_Rect button_sheet = buttons[sprite];
  switch (state) {
  case ButtonState::Unpressed:
		  return {button_sheet.x, button_sheet.y, button_sheet.w, button_sheet.h / 3};
    break;
  case ButtonState::Hover:
        return {button_sheet.x, button_sheet.y + button_sheet.h / 3, button_sheet.w, button_sheet.h / 3};
    break;
  case ButtonState::Pressed:
    return {button_sheet.x, button_sheet.y + (2 * button_sheet.h) / 3, button_sheet.w, button_sheet.h / 3};
    break;
  default:
    // TODO: error
    break;
  }
}


// MTODO: Possibly changes from ButtonState
inline SDL_Rect get_decoration(ButtonDecoration decoration)
{
if (auto x = get_if<CustomButtonDecoration>(&decoration)) {
return custom_decorations[*x];
}
else if (auto x = get_if<Entity>(&decoration)) {
	if (auto y = get_if<Unit>(x))
			{
					return units[*y];
			}
			else if (auto y = get_if<Animal>(x))
			{
					return animals[*y];
			}
			else if (auto y = get_if<Plant>(x))
			{
					return plants[*y];
			}
			else if (auto y = get_if<Buildable>(x))
			{
					return buildables[*y];
			}
			else
			{
					// TODO: error handling
					return null_sprite;
					
			}
}
return null_sprite;
}


inline SDL_Rect get_displayable(Displayable req)
{
if (auto c = std::get_if<Item>(&req))
	  {
            return items[*c];
	  }
	  else if (auto c = std::get_if<Buildable>(&req))
	  {
            return buildables[*c];
	  } /*
	  else if (auto c = std::get_if<knowledge::Academic>(&req)) {
	    return academic[c];
	  } else if (std::get_if<knowledge::Technology>(&req)) {
	    return knowledge[c];
		}
		*/
}
		
/*
 // TODO: add animation to subject display
SDL_Rect get_subject_display(Time age, EntityRenderData render_data)
{
	SDL_Rect* subject;
	if (auto animal_data = std::get_if<AnimalRenderData>(&render_data))
	{
	       return get_animal_rect(animal_data->animal, {Direction::South, ActionStatus::Idle, MatingStatus::Infertile}, age, 0, animal_infos[animal_data->animal]);
	}
	else if (auto unit_data = std::get_if<UnitRenderData>(&render_data))
	{
	       return get_unit_rect(unit_data->unit, ActionStatus::Idle, Direction::South, 0, age, unit_info);
	}
	else if (auto plant_data = std::get_if<PlantRenderData>(&render_data))
	{
	  sprite::get(plant_data->plant);
	} else if (auto buildable_data = std::get_if<BuildableRenderData>(&render_data))
	{
	  sprite::get(buildable_data->buildable);
	} else if (auto item_data  = std::get_if<ItemRenderData>(&render_data)) {
	  sprite::get(item_data->item);
	}
}
*/
class Info
{
public:
    uint8_t side_length;
    uint8_t side_height;
    uint8_t front_length;
    uint8_t front_height;

    uint8_t child_side_length;
    uint8_t child_side_height;
    uint8_t child_front_length;
    uint8_t child_front_height;

    uint8_t walking_sprite_length = 0;
    uint8_t running_sprite_length = 0;

    uint8_t walk_sprite_frame_length{};
    uint8_t run_sprite_frame_length{};
    uint8_t act_sprite_frame_length{};

    constexpr Info() = default;

    constexpr Info(uint8_t side_length, uint8_t side_height, uint8_t front_length,
			 uint8_t front_height, uint8_t child_side_length, uint8_t child_side_height,
			 uint8_t child_front_length,
			 uint8_t child_front_height)
        : side_length(side_length),
          side_height(side_height),
          front_length(front_length),
          front_height(front_height),
          child_side_length(child_side_length),
          child_side_height(child_side_height),
          child_front_length(child_front_length),
          child_front_height(child_front_height)
    {}
};

constexpr Info UNIT_SPRITE_INFO = Info(1,2,1,2,1,2,1,2);

inline constexpr LookupTable<Animal, Info> ANIMAL_SPRITE_INFOS = []
{
    LookupTable<Animal, Info> lt{};

    using enum Animal;

    lt[Pig]          = Info(2,1,1,2,2,1,1,2);
    lt[Cow]          = Info(3,2,1,3,3,2,2,2);
    lt[Chicken]      = Info(1,1,1,1,1,1,1,1);
    lt[Duck]         = Info(1,1,1,1,1,1,1,1);
    lt[Sheep]        = Info(2,1,1,2,2,1,1,1);
    lt[Goat]         = Info(2,1,1,2,2,1,1,1);
    lt[Horse]        = Info(3,2,1,3,3,2,1,3);
    lt[Ox]           = Info(3,2,1,3,3,2,1,3);
    lt[Donkey]       = Info(3,2,1,3,3,2,1,3);
    lt[Camel]        = Info(3,2,1,3,3,2,1,3);
    lt[WaterBuffalo] = Info(3,2,1,3,3,2,1,3);
    lt[Rabbit]       = Info(1,1,1,1,1,1,1,1);
    lt[Antelope]     = Info(3,2,1,2,2,2,1,2);
    lt[Deer]         = Info(2,2,1,2,2,2,1,2);
    lt[Moose]        = Info(4,3,2,3,3,2,2,3);
    lt[Capybara]     = Info(2,1,1,2,2,1,1,1);
    lt[Turtle]       = Info(1,1,1,1,1,1,1,1);
    lt[Elephant]     = Info(5,3,2,3,4,3,2,3);
    lt[Bison]        = Info(3,2,1,3,3,2,1,3);
    lt[Wolf]         = Info(3,2,1,3,3,2,1,3);
    lt[Bear]         = Info(3,2,1,3,2,2,1,2);
    lt[Caribou]      = Info(3,2,1,2,2,2,1,2);

    return lt;
}();

constexpr uint8_t MAX_STAGES = 4;

struct StageInfo {
	Coord dimensions;
	uint8_t stages;
	 constexpr StageInfo() = default;	
	constexpr StageInfo(Coord dimensions, uint8_t stages)
	    : dimensions(dimensions), stages(stages)
	{
	}
};

inline constexpr BitsetTable<Plant> PLANT_SPRITE_PROGRESSIVE_STAGES = []
	{
		BitsetTable<Plant> t{};
		using enum Plant;
		t.set(Moss);
		return t;
	}();


//farmable fruiting stages are a SEPARATE StageInfo. reminder that all trees that produce fruit start as default 'tree'
inline constexpr LookupTable<Plant, std::array<StageInfo, MAX_STAGES>> PLANT_SPRITE_DIMENSIONS = []
{
	LookupTable<Plant,std::array<StageInfo, MAX_STAGES>> lt{};
	using enum Plant;
	lt[Fern] = {{{{1,1}, 3}}};
	lt[Moss] = {{{{1,1}, 12}}};
	lt[Reed] = {{StageInfo({2,2}, 1)}};
	lt[Wheat] = {{StageInfo({1,2},4)}};
	lt[Oat] = {{StageInfo({1,1},3), StageInfo({1,2},2)}};
	lt[Rice] = {{StageInfo({1,1},5)}};
	lt[Bush] = {{StageInfo({1,1},4), StageInfo({2,2},3)}};
	lt[Papyrus] = {{ }}; //TODO
	lt[PioneerTree] = {{ }}; //TODO
	lt[DeciduousTree] = {{StageInfo({1,1},1),StageInfo({1,2},1), StageInfo({3,4},1)}}; //TODO (separate from regular 'tree', possibly, as those are unbarren fruit trees. make sure they are the same as the unbarren fruit trees)
	lt[EvergreenTree] = {{StageInfo({3,4},1)}}; //TODO: earlier stages
	lt[TropicalTree] = {{ {{5,3},1} }}; //TODO
	lt[Cactus] = {{ }}; // TODO
	lt[Grapevine] = {{StageInfo({1,1},2), StageInfo({2,2},2), StageInfo({3,2}, 4)}};
	lt[Lettuce] = {{ StageInfo({1,1},5)}};
	lt[Kale] = {{ StageInfo({1,1},4)}};
	lt[Corn] = {{ StageInfo({1,1},1), StageInfo({1,2},2), StageInfo({1,3},2)}};
	lt[Carrot] = {{ StageInfo({1,1}, 3), StageInfo({1,2}, 1)}};
	lt[Beets] = {{ StageInfo({1,1},3), StageInfo({1,1}, 1)}};
	lt[Potato] = {{ StageInfo({1,1}, 3), StageInfo({1,1}, 1)}};
	lt[Onion] = {{ StageInfo({1,1},1), StageInfo({1,2}, 4)}};
	lt[Garlic] = {{ StageInfo({1,1}, 4)}}; // likely change
	lt[Cabbage] = {{ StageInfo({1,1},5)}};
	lt[Broccoli] = {{ StageInfo({1,1},4)}};
	lt[Tomato] = {{StageInfo({1,1},1), StageInfo({1,2},1), StageInfo({2,2},3)}};
	lt[Cucumber] = {{StageInfo({1,1},5)}};
	lt[Pepper] = {{ StageInfo({1,1},1),StageInfo({1,2},2), StageInfo({2,2},3)}};
	//TODO lt[BlackPepper] = {{ StageInfo({})}};
	lt[Cotton] = {{ StageInfo({1,1},2), StageInfo({2,2},3)}};
	lt[Hemp] = {{StageInfo({1,1}, 4), StageInfo({1,2},1)}};
	lt[Flax] = {{ StageInfo({1,1},4)}};
	lt[Woad] = {{ StageInfo({1,1},4)}};
	lt[Madder] = {{ StageInfo({1,1},4)}};
	lt[Indigo] = {{ StageInfo({1,1},5)}};
	lt[Lavender] = {{StageInfo({1,1},3), StageInfo({1,2},1) }};
	lt[Mint] = {{StageInfo({1,1},4) }};
	lt[Thyme] = {{StageInfo({1,1},4) }};
	lt[Sage] = {{StageInfo({1,1},4)}};
	lt[Ginseng] = {{ StageInfo({1,1},6)}};
	lt[Rhubarb] = {{ StageInfo({1,1},5)}}; //TODO
	lt[Poppy] = {{ StageInfo({1,1},4)}};
	lt[Cocoa] = {{ StageInfo({1,1},1) , StageInfo({1,1},1),StageInfo({2,4},1)}};
	lt[Senna] = {{ StageInfo({1,2},1)}}; 
	lt[Saffron] = {{StageInfo({1,1},4)}};
	lt[AloeVera] = {{ StageInfo({1,1},3)}};
	lt[Orange] = {{ StageInfo({1,2},1), StageInfo({2,4},1)}};  
	lt[Apple] =  {{ StageInfo({1,2},1), StageInfo({2,4},1) }};
	lt[Lemon] = {{ StageInfo({1,2},1), StageInfo({2,4},1)}};
	lt[Pear] = {{ StageInfo({1,2},1), StageInfo({2,4},1)}};
	lt[Peach] = {{ StageInfo({1,2},1), StageInfo({2,4},1)}};
	lt[Cherry] = {{ StageInfo({1,2},1), StageInfo({2,4},1)}};
	lt[Apricot] = {{ StageInfo({1,2},1), StageInfo({2,4},1)}};
	lt[Plum] = {{ StageInfo({1,2},1), StageInfo({2,4},1)}};
	lt[Lime] = {{ StageInfo({1,2},1), StageInfo({2,4},1)}};
	lt[Olive] = {{ StageInfo({1,2},1), StageInfo({2,4},1)}};
	lt[Blueberry] = {{ StageInfo({1,1},4), StageInfo({2,2},2), StageInfo({2,3},1)}}; //TODO: fruited stages
	lt[Strawberry] = {{ StageInfo({1,1},4), StageInfo({2,2},2), StageInfo({2,3},1)}};
	return lt;
}();

inline constexpr LookupTable<Plant, uint8_t> PLANT_STAGE_AMOUNTS = []
{
	LookupTable<Plant, uint8_t> lt{};
	using enum Plant;
	for (size_t i = 0; i < static_cast<size_t>(Plant::MAX); i++)
	{
		Plant p = static_cast<Plant>(i);
		int s = 0;
		for (size_t j = 0; j < PLANT_SPRITE_DIMENSIONS[p].size(); j++)
			s += PLANT_SPRITE_DIMENSIONS[p][j].stages;
		lt[p] = s;
	}
	return lt;
}();

SDL_Rect get_plant(Plant plant, int stage)
{
        const std::array<sprite::StageInfo, sprite::MAX_STAGES> &sd = sprite::PLANT_SPRITE_DIMENSIONS[plant];
	StageInfo si = sprite::PLANT_SPRITE_DIMENSIONS[plant][stage];
	int tile_offset = 0;
	for (int i = 0; i < stage; i++)
		tile_offset += sd[i].dimensions.x;	
	return {plants[plant].x + tile_offset, plants[plant].y, (int)si.dimensions.x, (int)si.dimensions.y};
}

//items which can be stacked. need multiple layered versions.
inline constexpr LookupTable<Item, Coord> ITEM_DIMENSIONS = []
{
	LookupTable<Item, Coord> lt{};


	for (size_t i = 0; i < static_cast<uint16_t>(Item::MAX); i++)
	{
		lt[static_cast<Item>(i) ] = {1,1};
	}

	using enum Item;

	lt[Log] = {2,2};
	lt[Headdress] = {2,2};

	return lt;
}();

}
