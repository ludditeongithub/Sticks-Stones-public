// Stores hot arrays of sprite data (positions, sizes, colors, texture IDs), handles batching logic
#pragma once
#include "core/tables.hpp"
#include "ui/aggregates/info_box.hpp"
#include "ui/components/button.hpp"
#include "ui/components/element.hpp"
#include <world/item/enum.hpp>
#include <world/buildable/enum.hpp>
#include <world/animal/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/unit/enum.hpp>
#include <world/tile/enum.hpp>
#include <core/data.hpp>
#include <core/entity.hpp>
#include <variant>
#include <ui/components/button.hpp>
#include <json.hpp>

// TODO: right now this is only fitted for walk animations. need to make sure
// all the LOGIC is only fitted for walk animations, for now.

namespace sprite
{

using json = nlohmann::json;
// using Sprite = std::variant<Item, Plant, Tile, Grass, Animal, Unit, Buildable, ButtonSprite, UISprite>;

  RuntimeLookupTable<Animal, SDL_Rect> animal;

  inline constexpr LookupTable<Buildable, SDL_Rect> buildable = []
  {
	  LookupTable<Buildable, SDL_Rect> lt{};
	  using enum Buildable;

	  return lt;
  }();

  inline constexpr LookupTable<Plant,SDL_Rect> plant = [] {
    LookupTable<Plant,SDL_Rect> lt{};
    using enum Plant;
    
    return lt;
  }();

  inline constexpr LookupTable<Item,SDL_Rect> item = [] {
    LookupTable<Item,SDL_Rect> lt{};
    using enum Item;
    
    return lt;
  }();

  inline constexpr LookupTable<Tile,SDL_Rect> tile = [] {
    LookupTable<Tile,SDL_Rect> lt{};
    using enum Tile;
    
    return lt;
  }();


  inline constexpr LookupTable<Grass,SDL_Rect> grass = [] {
    LookupTable<Grass,SDL_Rect> lt{};
    using enum Grass;
    
    return lt;
  }();

  inline constexpr LookupTable<Unit,SDL_Rect> unit = [] {
    LookupTable<Unit,SDL_Rect> lt{};
    using enum Unit;
    
    return lt;
  }();


  inline constexpr LookupTable<ButtonSprite,SDL_Rect> button = [] {
    LookupTable<ButtonSprite,SDL_Rect> lt{};
    using enum ButtonSprite;
    
    return lt;
  }();


  inline constexpr LookupTable<CustomButtonDecoration,SDL_Rect> custom_decoration = [] {
    LookupTable<CustomButtonDecoration,SDL_Rect> lt{};
    using enum CustomButtonDecoration;
    
    return lt;
  }();

  inline constexpr LookupTable<UISprite,SDL_Rect> ui = [] {
    LookupTable<UISprite,SDL_Rect> lt{};
    using enum UISprite;
    
    return lt;
  }();


  inline constexpr LookupTable<Role,SDL_Rect> roles = [] {
    LookupTable<Role,SDL_Rect> lt{};
    using enum Role;
    
    return lt;
  }();
  
template<typename Sprite>
inline void save_sprite(int index, Sprite sprite, SCoord position, SCoord dimension)
{
	if (std::is_same<Animal, Sprite>::value) {
		animal[index] = SDL_Rect{position.x, position.y, dimension.x, dimension.y};	
        } else if (std::is_same<Buildable, Sprite>::value) {
		buildable[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Plant, Sprite>::value) {
		plant[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Item, Sprite>::value) {
		item[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Tile, Sprite>::value) {
		tile[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<Grass, Sprite>::value) {
		grass[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	} else if (std::is_same<ButtonUI, Sprite>::value) {
          button[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y}; // NOTE: since buttons have three states, the dimension is divided by 3.
	} else if (std::is_same<UISprite, Sprite>::value) {
		ui[index] = SDL_Rect{ position.x, position.y, dimension.x, dimension.y};
	}
	else if (std::is_same<Role, Sprite>::value) {
                roles[index] = SDL_Rect{position.x, position.y, dimension.x, dimension.y};
        } else if (std::is_same<CustomButtonDecoration, Sprite>::value) {
          custom_decoration[index] = SDL_Rect{position.x, position.y, dimension.x, dimension.y};
        } else throw std::invalid_argument("Invalid Sprite type.");
}

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

SDL_Rect get(Entity entity)
{
  if (auto x = std::get_if<Item>(entity)) {
    return item[static_cast<type>(name) ];
  } else if (auto x = std::get_if<Plant>(entity)) {
    return plant[static_cast<type>(name) ];
  } else if (auto x = std::get_if<Animal>(entity)) {
    return animal[static_cast<type>(name) ];
  } else if (auto x = std::get_if<Buildable>(entity)) {
    return buildable[static_cast<type>(name) ];
  } else if (auto x = std::get_if<Unit>(entity)) {
    return unit[entity];
  } x { // NullEntity
    // TODO: throw error
  }
}

  inline SDL_Rect get_button(ButtonSprite sprite, ButtonState state)
{
   SDL_Rect button_sheet = button[static_cast<int>(sprite)];
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
    return custom_decoration[static_cast<size_t>(*x)];
  } else
}

inline SDL_Rect get_displayable(Displayable display)
{
if (auto c = std::get_if<Item>(&req))
	  {
            return sprite::item[c];
	  }
	  else if (auto c = std::get_if<Buildable>(&req))
	  {
            return sprite::buildable[c];
          } else if (auto c = std::get_if<knowledge::Academic>(&req)) {
            return sprite::academic[c];
          } else if (std::get_if<knowledge::Technology>(&req)) {
            return sprite::knowledge[c];
          }
}

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

struct Info
{
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
	SDL_Rect dimensions;
	uint8_t stages;
	 constexpr StageInfo() = default;	
	constexpr StageInfo(SDL_Rect dimensions, uint8_t stages)
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

inline constexpr BitsetTable<Plant> PLANT_PRODUCES = []
	{
		BitsetTable<Plant> t{};
		using enum Plant;
	t.set(Wheat);
	t.set(Oat);
	t.set(Rice);
	t.set(Papyrus);
	t.set(Cactus);
	t.set(Grapevine);
	t.set(Lettuce);
	t.set(Kale);
	t.set(Corn);
	t.set(Carrot);
	t.set(Beets);
	t.set(Potato);
	t.set(Onion);
	t.set(Garlic);
	t.set(Cabbage);
	t.set(Broccoli);
	t.set(Tomato);
	t.set(Cucumber);
	t.set(Pepper);
	t.set(BlackPepper);
	t.set(Cotton);
	t.set(Hemp);
	t.set(Flax);
	t.set(Woad);
	t.set(Madder);
	t.set(Indigo);
	t.set(Lavender);
	t.set(Mint);
	t.set(Thyme);
	t.set(Sage);
	t.set(Ginseng);
	t.set(Rhubarb);
	t.set(Cocoa);
	t.set(Senna);
	t.set(Saffron);
	t.set(AloeVera);
	t.set(Orange);
	t.set(Apple);
	t.set(Lemon);
	t.set(Pear);
	t.set(Peach);
	t.set(Cherry);
	t.set(Apricot);
	t.set(Plum);
	t.set(Lime);
	t.set(Blueberry);
	t.set(Strawberry);
	t.set(Olive);
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

}
