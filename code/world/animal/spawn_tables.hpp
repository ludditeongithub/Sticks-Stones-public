#include "enum.hpp"
#include "world/tile/grass.hpp"
#include <world/tile/enum.hpp>
#include <core/tables.hpp>

namespace animal
{

inline constexpr LookupTable<Animal, SCoord> temperature_penalty_ranges = []
{
	LookupTable<Animal, SCoord> lt{};
	using enum Animal;

	lt[Pig]          = {23, 77};
	lt[Cow]          = {14, 77};
	lt[Chicken]      = {50, 86};
	lt[Duck]         = {32, 77};
	lt[Sheep]        = {14, 68};
	lt[Goat]         = {41, 86};
	lt[Horse]        = {14, 77};
	lt[Ox]           = {14, 77};
	lt[Donkey]       = {50, 95};
	lt[Camel]        = {59, 104};
	lt[WaterBuffalo] = {68, 95};
	lt[Rabbit]       = {41, 68};
	lt[Antelope]     = {50, 95};
	lt[Deer]         = {14, 68};
	lt[Moose]        = {-4, 59};
	lt[Capybara]     = {68, 95};
	lt[Turtle]       = {68, 95};
	lt[Elephant]     = {68, 95};
	lt[Bison]        = {-4, 68};
	lt[Wolf]         = {-4, 59};
	lt[Bear]         = {5, 68};
	lt[Caribou]      = {-13, 50};

	return lt;
}();

inline constexpr LookupTable<Animal, Coord> humidity_penalty_ranges = []
{
	LookupTable<Animal, Coord> lt{};
	using enum Animal;

	lt[Pig]          = {50, 80};
	lt[Cow]          = {40, 80};
	lt[Chicken]      = {40, 70};
	lt[Duck]         = {60, 100};
	lt[Sheep]        = {30, 70};
	lt[Goat]         = {20, 60};
	lt[Horse]        = {30, 70};
	lt[Ox]           = {30, 70};
	lt[Donkey]       = {20, 50};
	lt[Camel]        = {10, 40};
	lt[WaterBuffalo] = {60, 100};
	lt[Rabbit]       = {40, 70};
	lt[Antelope]     = {20, 60};
	lt[Deer]         = {40, 80};
	lt[Moose]        = {50, 90};
	lt[Capybara]     = {70, 100};
	lt[Turtle]       = {60, 100};
	lt[Elephant]     = {40, 80};
	lt[Bison]        = {30, 70};
	lt[Wolf]         = {40, 80};
	lt[Bear]         = {40, 80};
	lt[Caribou]      = {40, 90};

	return lt;
}();
  
constexpr float dominant = 0.003;
constexpr float abundant = 0.0015;
constexpr float common = 0.0008;
constexpr float semicommon = 0.0004;
constexpr float uncommon = 0.0002;
constexpr float rare = 0.00008;
constexpr float veryrare = 0.00003;
constexpr float endangered = 0.00001;
constexpr float never = 0.0;

inline constexpr LookupTable2D<Biome, Animal, float> biome_spawn_chances = []
{
	LookupTable2D<Biome, Animal, float> lt{};
	using enum Animal;

        lt[Biome::HotDesert][Pig]          = rare;
        lt[Biome::HotDesert][Camel]        = dominant;
        lt[Biome::HotDesert][WaterBuffalo] = uncommon;
        lt[Biome::HotDesert][Rabbit]       = common;
        lt[Biome::HotDesert][Antelope]     = abundant;
        lt[Biome::HotDesert][Wolf]         = semicommon;
        lt[Biome::HotDesert][Bear]         = veryrare;

        lt[Biome::Grassland][Pig]      = common;
        lt[Biome::Grassland][Cow]      = abundant;
        lt[Biome::Grassland][Sheep]    = abundant;
        lt[Biome::Grassland][Goat]     = semicommon;
        lt[Biome::Grassland][Horse]    = dominant;
        lt[Biome::Grassland][Ox]       = semicommon;
        lt[Biome::Grassland][Donkey]   = uncommon;
        lt[Biome::Grassland][Rabbit]   = abundant;
        lt[Biome::Grassland][Antelope] = abundant;
        lt[Biome::Grassland][Bison]    = dominant;
        lt[Biome::Grassland][Wolf]     = semicommon;
        lt[Biome::Grassland][Bear]     = rare;
        lt[Biome::Grassland][Caribou]  = never;

        lt[Biome::Savanna][Pig]          = rare;
        lt[Biome::Savanna][Cow]          = common;
        lt[Biome::Savanna][Sheep]        = uncommon;
        lt[Biome::Savanna][Goat]         = semicommon;
        lt[Biome::Savanna][Camel]        = rare;
        lt[Biome::Savanna][WaterBuffalo] = uncommon;
        lt[Biome::Savanna][Rabbit]       = common;
        lt[Biome::Savanna][Antelope]     = abundant;
        lt[Biome::Savanna][Elephant]     = dominant;
        lt[Biome::Savanna][Bison]        = rare;
        lt[Biome::Savanna][Wolf]         = semicommon;
        lt[Biome::Savanna][Bear]         = rare;
        lt[Biome::Savanna][Caribou]      = never;

        lt[Biome::Wetland][Pig]          = common;
        lt[Biome::Wetland][Cow]          = uncommon;
        lt[Biome::Wetland][Sheep]        = rare;
        lt[Biome::Wetland][Goat]         = rare;
        lt[Biome::Wetland][Camel]        = rare;
        lt[Biome::Wetland][WaterBuffalo] = dominant;
        lt[Biome::Wetland][Rabbit]       = semicommon;
        lt[Biome::Wetland][Antelope]     = abundant;
        lt[Biome::Wetland][Elephant]     = semicommon;
        lt[Biome::Wetland][Bison]        = rare;
        lt[Biome::Wetland][Wolf]         = uncommon;
        lt[Biome::Wetland][Bear]         = semicommon;
        lt[Biome::Wetland][Caribou]      = never;

        lt[Biome::Temperate][Pig]      = semicommon;
        lt[Biome::Temperate][Cow]      = common;
        lt[Biome::Temperate][Sheep]    = uncommon;
        lt[Biome::Temperate][Goat]     = semicommon;
        lt[Biome::Temperate][Horse]    = rare;
        lt[Biome::Temperate][Ox]       = uncommon;
        lt[Biome::Temperate][Donkey]   = rare;
        lt[Biome::Temperate][Rabbit]   = abundant;
        lt[Biome::Temperate][Antelope] = rare;
        lt[Biome::Temperate][Deer]     = dominant;
        lt[Biome::Temperate][Moose]    = abundant;
        lt[Biome::Temperate][Wolf]     = semicommon;
        lt[Biome::Temperate][Bear]     = dominant;
        lt[Biome::Temperate][Caribou]  = never;

        lt[Biome::Boreal][Pig]      = rare;
        lt[Biome::Boreal][Cow]      = rare;
        lt[Biome::Boreal][Sheep]    = rare;
        lt[Biome::Boreal][Goat]     = rare;
        lt[Biome::Boreal][Horse]    = rare;
        lt[Biome::Boreal][Ox]       = rare;
        lt[Biome::Boreal][Donkey]   = rare;
        lt[Biome::Boreal][Rabbit]   = semicommon;
        lt[Biome::Boreal][Antelope] = never;
        lt[Biome::Boreal][Deer]     = abundant;
        lt[Biome::Boreal][Moose]    = dominant;
        lt[Biome::Boreal][Bison]    = rare;
        lt[Biome::Boreal][Wolf]     = semicommon;
        lt[Biome::Boreal][Bear]     = abundant;
        lt[Biome::Boreal][Caribou]  = dominant;

        lt[Biome::Jungle][Pig]      = rare;
        lt[Biome::Jungle][Cow]      = veryrare;
        lt[Biome::Jungle][Horse]    = rare;
        lt[Biome::Jungle][Ox]       = veryrare;
        lt[Biome::Jungle][Donkey]   = rare;
        lt[Biome::Jungle][Rabbit]   = rare;
        lt[Biome::Jungle][Antelope] = rare;
        lt[Biome::Jungle][Elephant] = abundant;
        lt[Biome::Jungle][Wolf]     = rare;
        lt[Biome::Jungle][Bear]     = rare;
        lt[Biome::Jungle][Caribou]  = never;

        lt[Biome::Rocky][Goat]  = common;
        lt[Biome::Rocky][Wolf]  = rare;
        lt[Biome::Rocky][Sheep] = rare;

        lt[Biome::Tundra][Pig]      = never;
        lt[Biome::Tundra][Cow]      = never;
        lt[Biome::Tundra][Sheep]    = rare;
        lt[Biome::Tundra][Goat]     = uncommon;
        lt[Biome::Tundra][Horse]    = never;
        lt[Biome::Tundra][Ox]       = rare;
        lt[Biome::Tundra][Donkey]   = never;
        lt[Biome::Tundra][Rabbit]   = semicommon;
        lt[Biome::Tundra][Antelope] = never;
        lt[Biome::Tundra][Elephant] = never;
        lt[Biome::Tundra][Bison]    = never;
        lt[Biome::Tundra][Wolf]     = abundant;
        lt[Biome::Tundra][Bear]     = rare;
        lt[Biome::Tundra][Caribou] = dominant;
    return lt;
  }();
};
