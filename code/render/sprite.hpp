// Stores hot arrays of sprite data (positions, sizes, colors, texture IDs), handles batching logic
#pragma once
#include "ui/components/element.hpp"
#include <world/item/enum.hpp>
#include <world/buildable/enum.hpp>
#include <world/animal/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/unit/enum.hpp>
#include <world/tile/enum.hpp>
#include <core/data.hpp>
#include <variant>
#include <ui/components/button.hpp>
#include <iostream>
#include <memory>

// TODO: right now this is only fitted for walk animations. need to make sure
// all the LOGIC is only fitted for walk animations, for now.

struct SpriteInfo
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

    constexpr SpriteInfo() = default;

    constexpr SpriteInfo(uint8_t side_length, uint8_t side_height, uint8_t front_length,
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

constexpr SpriteInfo UNIT_SPRITE_INFO = SpriteInfo(1,2,1,2,1,2,1,2);

inline constexpr LookupTable<Animal, SpriteInfo> ANIMAL_SPRITE_INFOS = []
{
    LookupTable<Animal, SpriteInfo> lt{};

    using enum Animal;

    lt[Pig]          = SpriteInfo(2,1,1,2,2,1,1,2);
    lt[Cow]          = SpriteInfo(3,2,1,3,3,2,2,2);
    lt[Chicken]      = SpriteInfo(1,1,1,1,1,1,1,1);
    lt[Duck]         = SpriteInfo(1,1,1,1,1,1,1,1);
    lt[Sheep]        = SpriteInfo(2,1,1,2,2,1,1,1);
    lt[Goat]         = SpriteInfo(2,1,1,2,2,1,1,1);
    lt[Horse]        = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Ox]           = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Donkey]       = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Camel]        = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[WaterBuffalo] = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Rabbit]       = SpriteInfo(1,1,1,1,1,1,1,1);
    lt[Antelope]     = SpriteInfo(3,2,1,2,2,2,1,2);
    lt[Deer]         = SpriteInfo(2,2,1,2,2,2,1,2);
    lt[Moose]        = SpriteInfo(4,3,2,3,3,2,2,3);
    lt[Capybara]     = SpriteInfo(2,1,1,2,2,1,1,1);
    lt[Turtle]       = SpriteInfo(1,1,1,1,1,1,1,1);
    lt[Elephant]     = SpriteInfo(5,3,2,3,4,3,2,3);
    lt[Bison]        = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Wolf]         = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Bear]         = SpriteInfo(3,2,1,3,2,2,1,2);
    lt[Caribou]      = SpriteInfo(3,2,1,2,2,2,1,2);

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
