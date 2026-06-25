#include "enum.hpp"
#include <core/tables.hpp>
#include <world/tile/enum.hpp>
#include <core/data.hpp>

namespace plant
{

  inline constexpr LookupTable2D<Biome, PlantCategory, float> categorySpawnChances = [] {
    LookupTable2D<Biome, PlantCategory, float> lt{};
  using enum PlantCategory;
   	lt[Biome::HotDesert][Tree] = 0.04; // acacia
	lt[Biome::HotDesert][Citrus] = 0.0;
	lt[Biome::HotDesert][Stone] = 0.0;
	lt[Biome::HotDesert][Pome] = 0.0;
	lt[Biome::HotDesert][Olive] = 0.06;
	lt[Biome::HotDesert][Moss] = 0.0;
	lt[Biome::HotDesert][Fern] = 0.0;
	lt[Biome::HotDesert][Bush] = 0.45;
	lt[Biome::HotDesert][Succulent] = 0.7;
	lt[Biome::HotDesert][BerryShrub] = 0.0;
	lt[Biome::HotDesert][Leafy] = 0.00;
	lt[Biome::HotDesert][Root] = 0.0;
	lt[Biome::HotDesert][Bulb] = 0.06;
	lt[Biome::HotDesert][Grain] = 0.0;
	lt[Biome::HotDesert][Grapevine] = 0.0;
	lt[Biome::HotDesert][Herb] = 0.075;
	lt[Biome::HotDesert][Textile] = 0.02;

        lt[Biome::Grassland][Tree] = 0.2;
	lt[Biome::Grassland][Citrus] = 0.005;
	lt[Biome::Grassland][Stone] = 0.005;
	lt[Biome::Grassland][Pome] = 0.005;
	lt[Biome::Grassland][Olive] = 0.005;
	lt[Biome::Grassland][Moss] = 0.2;
	lt[Biome::Grassland][Fern] = 0.2;
	lt[Biome::Grassland][Bush] = 0.3;
	lt[Biome::Grassland][Succulent] = 0.06;
	lt[Biome::Grassland][BerryShrub] = 0.2;
	lt[Biome::Grassland][Leafy] = 0.2;
	lt[Biome::Grassland][Root] = 0.1;
	lt[Biome::Grassland][Reed] = 0.0;
	lt[Biome::Grassland][Bulb] = 0.06;
	lt[Biome::Grassland][Grain] = 0.35;
	lt[Biome::Grassland][Grapevine] = 0.0;
	lt[Biome::Grassland][Herb] = 0.25;
	lt[Biome::Grassland][Textile] = 0.06;

        lt[Biome::Savanna][Tree] = 0.80;
	lt[Biome::Savanna][Citrus] = 0.08;
	lt[Biome::Savanna][Stone] = 0.08;
	lt[Biome::Savanna][Pome] = 0.0;
	lt[Biome::Savanna][Olive] = 0.08;
	lt[Biome::Savanna][Moss] = 0.04;
	lt[Biome::Savanna][Fern] = 0.08;
	lt[Biome::Savanna][Bush] = 0.6;
	lt[Biome::Savanna][Succulent] = 0.16;
	lt[Biome::Savanna][BerryShrub] = 0.12;
	lt[Biome::Savanna][Leafy] = 0.08;
	lt[Biome::Savanna][Root] = 0.1;
	lt[Biome::Savanna][Bulb] = 0.12;
	lt[Biome::Savanna][Grain] = 0.2;
	lt[Biome::Savanna][Grapevine] = 0.0;
	lt[Biome::Savanna][Herb] = 0.2;
	lt[Biome::Savanna][Textile] = 0.04;

        lt[Biome::Wetland][Tree] = 0.3;
	lt[Biome::Wetland][Citrus] = 0.0;
	lt[Biome::Wetland][Stone] = 0.0;
	lt[Biome::Wetland][Pome] = 0.0;
	lt[Biome::Wetland][Olive] = 0.0;
	lt[Biome::Wetland][Moss] = 0.15;
	lt[Biome::Wetland][Fern] = 0.3;
	lt[Biome::Wetland][Bush] = 0.3;
	lt[Biome::Wetland][Reed] = 0.4;
	lt[Biome::Wetland][Succulent] = 0.06;
	lt[Biome::Wetland][BerryShrub] = 0.09;
	lt[Biome::Wetland][Leafy] = 0.0; // increase when adding duckweed and lt] water plants
	lt[Biome::Wetland][Root] = 0.0;	 // increase when adding wetland root plants
	lt[Biome::Wetland][Bulb] = 0.0;
	lt[Biome::Wetland][Grain] = 0.3;
	lt[Biome::Wetland][Grapevine] = 0.0;
	lt[Biome::Wetland][Herb] = 0.3;
	lt[Biome::Wetland][Textile] = 0.02;

        lt[Biome::Temperate][Tree] = 0.92;
	lt[Biome::Temperate][Citrus] = 0.02;
	lt[Biome::Temperate][Stone] = 0.02;
	lt[Biome::Temperate][Pome] = 0.0;
	lt[Biome::Temperate][Olive] = 0.0;
	lt[Biome::Temperate][Moss] = 0.25;
	lt[Biome::Temperate][Fern] = 0.35;
	lt[Biome::Temperate][Bush] = 0.2;
	lt[Biome::Temperate][Reed] = 0.05;
	lt[Biome::Temperate][Succulent] = 0.04;
	lt[Biome::Temperate][BerryShrub] = 0.1;
	lt[Biome::Temperate][Leafy] = 0.1;
	lt[Biome::Temperate][Root] = 0.1;
	lt[Biome::Temperate][Bulb] = 0.07;
	lt[Biome::Temperate][Grain] = 0.1;
	lt[Biome::Temperate][Grapevine] = 0.04;
	lt[Biome::Temperate][Herb] = 0.18;
	lt[Biome::Temperate][Textile] = 0.02;

        lt[Biome::Boreal][Tree] = 0.85;
	lt[Biome::Boreal][Citrus] = 0.0;
	lt[Biome::Boreal][Stone] = 0.0;
	lt[Biome::Boreal][Pome] = 0.0;
	lt[Biome::Boreal][Olive] = 0.0;
	lt[Biome::Boreal][Moss] = 0.2;
	lt[Biome::Boreal][Fern] = 0.14;
	lt[Biome::Boreal][Bush] = 0.2;
	lt[Biome::Boreal][Succulent] = 0.02;
	lt[Biome::Boreal][BerryShrub] = 0.2;
	lt[Biome::Boreal][Leafy] = 0.08;
	lt[Biome::Boreal][Root] = 0.08;
	lt[Biome::Boreal][Bulb] = 0.04;
	lt[Biome::Boreal][Grain] = 0.06;
	lt[Biome::Boreal][Grapevine] = 0.0;
	lt[Biome::Boreal][Herb] = 0.08;
	lt[Biome::Boreal][Textile] = 0.02;

        lt[Biome::Jungle][Tree] = 0.85;
	lt[Biome::Jungle][Citrus] = 0.02;
	lt[Biome::Jungle][Stone] = 0.02;
	lt[Biome::Jungle][Pome] = 0.0;
	lt[Biome::Jungle][Olive] = 0.0;
	lt[Biome::Jungle][Moss] = 0.2;
	lt[Biome::Jungle][Fern] = 0.3;
	lt[Biome::Jungle][Bush] = 0.2;
	lt[Biome::Jungle][Reed] = 0.02;
	lt[Biome::Jungle][Succulent] = 0.0;
	lt[Biome::Jungle][BerryShrub] = 0.2;
	lt[Biome::Jungle][Leafy] = 0.05; // add more later
	lt[Biome::Jungle][Root] = 0.06;
	lt[Biome::Jungle][Bulb] = 0.04;
	lt[Biome::Jungle][Grain] = 0.07;
	lt[Biome::Jungle][Grapevine] = 0.04;
	lt[Biome::Jungle][Herb] = 0.18;
	lt[Biome::Jungle][Textile] = 0.02;

        lt[Biome::Rocky][Tree] = 0.114108f;
	lt[Biome::Rocky][Moss] = 0.342324f;
	lt[Biome::Rocky][Fern] = 0.114108f;
	lt[Biome::Rocky][Succulent] = 0.186722f;
	lt[Biome::Rocky][BerryShrub] = 0.082988f;
	lt[Biome::Rocky][Leafy] = 0.020747f;
	lt[Biome::Rocky][Root] = 0.031121f;
	lt[Biome::Rocky][Herb] = 0.082988f;
	lt[Biome::Rocky][Textile] = 0.004149f;

        lt[Biome::Tundra][Moss] = 0.6;
	lt[Biome::Tundra][Fern] = 0.06;
	lt[Biome::Tundra][Bush] = 0.4;
	lt[Biome::Tundra][Succulent] = 0.07;
	lt[Biome::Tundra][Leafy] = 0.2;
	lt[Biome::Tundra][Root] = 0.2;
	lt[Biome::Tundra][Herb] = 0.02;

        lt[Biome::ColdDesert][Moss] = 0.2;
	lt[Biome::ColdDesert][Fern] = 0.05;
	lt[Biome::ColdDesert][Bush] = 0.3;
	lt[Biome::ColdDesert][Succulent] = 0.2;
	lt[Biome::ColdDesert][BerryShrub] = 0.05;
	lt[Biome::ColdDesert][Leafy] = 0.15;
	lt[Biome::ColdDesert][Root] = 0.15;
	lt[Biome::ColdDesert][Bulb] = 0.05;
	lt[Biome::ColdDesert][Grain] = 0.0;
	lt[Biome::ColdDesert][Grapevine] = 0.0;
	lt[Biome::ColdDesert][Herb] = 0.02;
	lt[Biome::ColdDesert][Textile] = 0.03;
  return lt;
 }();

inline constexpr LookupTable<Plant, Coord> temperaturePenaltyRanges = []
{
	LookupTable<Plant, Coord> lt{};
	using enum Plant;
        lt[DeciduousTree] = {64, 77};
        lt[EvergreenTree] = {46, 68};
        lt[PioneerTree] = {55, 86};
        lt[TropicalTree] = {73, 87};
        lt[Moss] = {40, 75};
        lt[Bush] = {45, 86};
        lt[Cactus] = {45, 86};
        lt[Lemon] = {68, 85};
        lt[Lime] = {75, 90};
        lt[Orange] = {65, 85};
        lt[Peach] = {60, 80};
        lt[Plum] = {55, 75};
        lt[Cherry] = {50, 72};
        lt[Apple] = {50, 72};
        lt[Pear] = {55, 75};
        lt[Olive] = {61, 80};
        lt[Blueberry] = {60, 72};
        lt[Strawberry] = {61, 75};
        lt[Grapevine] = {60, 80};
        lt[Wheat] = {55, 75};
        lt[Rice] = {75, 92};
        lt[Oat] = {60, 80};
        lt[Lettuce] = {50, 72};
        lt[Kale] = {45, 70};
        lt[Carrot] = {56, 69};
        lt[Beets] = {56, 69};
        lt[Potato] = {60, 67};
        lt[Onion] = {60, 70};
        lt[Garlic] = {55, 68};
        lt[Tomato] = {69, 81};
        lt[Cucumber] = {70, 85};
        lt[Pepper] = {70, 85};
        lt[Cotton] = {65, 85};
        lt[Hemp] = {60, 80};
        lt[Flax] = {55, 75};
        lt[Fern] = {50, 72};
        lt[Reed] = {55, 85};
	return lt;
}();


inline constexpr LookupTable<Plant, Coord> humidityPenaltyRanges = []
{
	LookupTable<Plant, Coord> lt{};
	using enum Plant;
        lt[DeciduousTree] = {52, 78};
        lt[EvergreenTree]     = {60, 87};
        lt[PioneerTree]       = {50, 80};
        lt[TropicalTree]      = {80, 120};
        lt[Moss]          = {85, 120};
        lt[Bush]          = {60, 87};
        lt[Cactus]         = {1, 30};

        lt[Lemon]         = {50, 70};
        lt[Lime]          = {60, 85};
        lt[Orange]        = {45, 70};

        lt[Peach]         = {40, 65};
        lt[Plum]          = {45, 70};
        lt[Cherry]        = {45, 65};
        lt[Apple]         = {50, 75};
        lt[Pear]          = {55, 80};
        lt[Olive]         = {33, 58};

        lt[Blueberry]   = {70, 90};
        lt[Strawberry]  = {60, 85};
        lt[Grapevine]        = {45, 65};

        lt[Wheat]         = {45, 70};
        lt[Rice]          = {75, 100};
        lt[Oat]           = {45, 68};

        lt[Lettuce]       = {65, 88};
        lt[Kale]          = {65, 88};
        lt[Carrot]        = {55, 78};
        lt[Beets]         = {55, 78};
        lt[Potato]      = {65, 88};
        lt[Onion]         = {55, 77};
        lt[Garlic]        = {50, 70};

        lt[Tomato]        = {55, 78};
        lt[Cucumber]      = {60, 85};
        lt[Pepper]        = {55, 75};

        lt[Cotton]        = {50, 75};
        lt[Hemp]          = {55, 80};
        lt[Flax]          = {50, 70};

        lt[Fern]          = {75, 115};
        lt[Reed]          = {80, 120}; 
	return lt;
}();

  float optimal = 1.0;
		float great = 0.5;
		float good = 0.25;
		float poorly = 0.125;
		float rarely = 0.6325;


inline LookupTable2D<Plant, Tile, float> tileSpawnMultipliers = []
{
	LookupTable2D<Plant, Tile, float> lt{};
	using enum Tile;
// Deciduous
					
	lt[Plant::DeciduousTree][Podzol] = poorly;
	lt[Plant::DeciduousTree][LoamSoil] = optimal;
	lt[Plant::DeciduousTree][PeatSoil] = poorly;
	lt[Plant::DeciduousTree][SandySoil] = poorly;
	lt[Plant::DeciduousTree][ClaySoil] = poorly;
	lt[Plant::DeciduousTree][SiltySoil] = optimal;
	lt[Plant::DeciduousTree][RockySoil] = poorly;
	lt[Plant::DeciduousTree][AridSoil] = poorly;
	lt[Plant::DeciduousTree][Oxisol] = poorly;
	lt[Plant::DeciduousTree][Gleysol] = rarely;
	
					
					
	lt[Plant::EvergreenTree][Podzol] = good;
	lt[Plant::EvergreenTree][LoamSoil] = good;
	lt[Plant::EvergreenTree][PeatSoil] = poorly;
	lt[Plant::EvergreenTree][SandySoil] = good;
	lt[Plant::EvergreenTree][ClaySoil] = poorly;
	lt[Plant::EvergreenTree][SiltySoil] = good;
	lt[Plant::EvergreenTree][RockySoil] = poorly;
	lt[Plant::EvergreenTree][AridSoil] = rarely;
	lt[Plant::EvergreenTree][Oxisol] = poorly;
	lt[Plant::EvergreenTree][Gleysol] = poorly;	
					
	lt[Plant::PioneerTree][Podzol] = rarely;
	lt[Plant::PioneerTree][LoamSoil] = optimal;
	lt[Plant::PioneerTree][PeatSoil] = great;
	lt[Plant::PioneerTree][SandySoil] = good;
	lt[Plant::PioneerTree][ClaySoil] = poorly;
	lt[Plant::PioneerTree][SiltySoil] = optimal;
	lt[Plant::PioneerTree][RockySoil] = rarely;
	lt[Plant::PioneerTree][AridSoil] = poorly;
	lt[Plant::PioneerTree][Oxisol] = poorly;
	lt[Plant::PioneerTree][Gleysol] = great;
	
  	// Tropical
					
	lt[Plant::TropicalTree][Podzol] = poorly;
	lt[Plant::TropicalTree][LoamSoil] = optimal;
	lt[Plant::TropicalTree][PeatSoil] = great;
	lt[Plant::TropicalTree][SandySoil] = good;
	lt[Plant::TropicalTree][ClaySoil] = rarely;
	lt[Plant::TropicalTree][SiltySoil] = good;
	lt[Plant::TropicalTree][Oxisol] = optimal;
	lt[Plant::TropicalTree][Gleysol] = optimal;
	
  // Moss
				
	lt[Plant::Moss][Podzol] = great;
	lt[Plant::Moss][LoamSoil] = great;
	lt[Plant::Moss][PeatSoil] = optimal;
	lt[Plant::Moss][SandySoil] = good;
	lt[Plant::Moss][ClaySoil] = good;
	lt[Plant::Moss][SiltySoil] = great;
	lt[Plant::Moss][RockySoil] = great;		
	lt[Plant::Moss][Oxisol] = poorly;
	lt[Plant::Moss][Gleysol] = optimal;			
	
  // Bush 
	lt[Plant::Bush][Podzol] = optimal;
	lt[Plant::Bush][LoamSoil] = optimal;
	lt[Plant::Bush][PeatSoil] = great;
	lt[Plant::Bush][SandySoil] = good;
	lt[Plant::Bush][ClaySoil] = good;
	lt[Plant::Bush][SiltySoil] = great;
	lt[Plant::Bush][RockySoil] = poorly;
	lt[Plant::Bush][AridSoil] = rarely;
	lt[Plant::Bush][Oxisol] = great;
	lt[Plant::Bush][Gleysol] = great;			
				
  // Cacti
				
	lt[Plant::Cactus][Podzol] = rarely;
	lt[Plant::Cactus][LoamSoil] = great;
	lt[Plant::Cactus][PeatSoil] = poorly;
	lt[Plant::Cactus][SandySoil] = optimal;
	lt[Plant::Cactus][ClaySoil] = good;
	lt[Plant::Cactus][SiltySoil] = great;
	lt[Plant::Cactus][RockySoil] = good;
	lt[Plant::Cactus][AridSoil] = optimal;
	lt[Plant::Cactus][Oxisol] = great;
	lt[Plant::Cactus][Gleysol] = rarely;	
			
// Lemon

	lt[Plant::Lemon][Podzol] = poorly;
	lt[Plant::Lemon][LoamSoil] = optimal;
	lt[Plant::Lemon][PeatSoil] = poorly;
	lt[Plant::Lemon][SandySoil] = great;
	lt[Plant::Lemon][ClaySoil] = poorly;
	lt[Plant::Lemon][SiltySoil] = good;
	lt[Plant::Lemon][RockySoil] = rarely;
	lt[Plant::Lemon][AridSoil] = poorly;
	lt[Plant::Lemon][Oxisol] = good;



// Lime

	lt[Plant::Lime][Podzol] = poorly;
	lt[Plant::Lime][LoamSoil] = great;
	lt[Plant::Lime][PeatSoil] = poorly;
	lt[Plant::Lime][SandySoil] = optimal;
	lt[Plant::Lime][ClaySoil] = poorly;
	lt[Plant::Lime][SiltySoil] = good;
	lt[Plant::Lime][RockySoil] = rarely;
	lt[Plant::Lime][AridSoil] = poorly;
	lt[Plant::Lime][Oxisol] = great;
	


// Orange

	lt[Plant::Orange][Podzol] = poorly;
	lt[Plant::Orange][LoamSoil] = optimal;
	lt[Plant::Orange][PeatSoil] = poorly;
	lt[Plant::Orange][SandySoil] = great;
	lt[Plant::Orange][ClaySoil] = good;
	lt[Plant::Orange][SiltySoil] = great;
	lt[Plant::Orange][RockySoil] = poorly;
	lt[Plant::Orange][AridSoil] = poorly;
	lt[Plant::Orange][Oxisol] = good;


// Peach  
	lt[Plant::Peach][Podzol] = poorly;
	lt[Plant::Peach][LoamSoil] = optimal;
	lt[Plant::Peach][PeatSoil] = rarely;
	lt[Plant::Peach][SandySoil] = great;
	lt[Plant::Peach][ClaySoil] = poorly;
	lt[Plant::Peach][SiltySoil] = good;
	lt[Plant::Peach][RockySoil] = poorly;
	lt[Plant::Peach][AridSoil] = good;
	lt[Plant::Peach][Oxisol] = poorly;
	lt[Plant::Peach][Gleysol] = rarely;


// Plum
	lt[Plant::Plum][Podzol] = poorly;
	lt[Plant::Plum][LoamSoil] = optimal;
	lt[Plant::Plum][PeatSoil] = poorly;
	lt[Plant::Plum][SandySoil] = good;
	lt[Plant::Plum][ClaySoil] = good;
	lt[Plant::Plum][SiltySoil] = great;
	lt[Plant::Plum][RockySoil] = poorly;
	lt[Plant::Plum][AridSoil] = poorly;
	lt[Plant::Plum][Oxisol] = poorly;
	lt[Plant::Plum][Gleysol] = poorly;

  // Cherry
	lt[Plant::Cherry][Podzol] = poorly;
	lt[Plant::Cherry][LoamSoil] = optimal;
	lt[Plant::Cherry][PeatSoil] = rarely;
	lt[Plant::Cherry][SandySoil] = good;
	lt[Plant::Cherry][ClaySoil] = poorly;
	lt[Plant::Cherry][SiltySoil] = great;
	lt[Plant::Cherry][RockySoil] = poorly;
	lt[Plant::Cherry][AridSoil] = rarely;
	lt[Plant::Cherry][Oxisol] = poorly;
	lt[Plant::Cherry][Gleysol] = rarely;
  
// Apple

	lt[Plant::Apple][Podzol] = poorly;
	lt[Plant::Apple][LoamSoil] = optimal;
	lt[Plant::Apple][PeatSoil] = poorly;
	lt[Plant::Apple][SandySoil] = good;
	lt[Plant::Apple][ClaySoil] = good;
	lt[Plant::Apple][SiltySoil] = great;
	lt[Plant::Apple][RockySoil] = poorly;
	lt[Plant::Apple][AridSoil] = rarely;
	lt[Plant::Apple][Oxisol] = poorly;
	lt[Plant::Apple][Gleysol] = poorly;


// Pear

	lt[Plant::Pear][Podzol] = poorly;
	lt[Plant::Pear][LoamSoil] = optimal;
	lt[Plant::Pear][PeatSoil] = poorly;
	lt[Plant::Pear][SandySoil] = good;
	lt[Plant::Pear][ClaySoil] = great;
	lt[Plant::Pear][SiltySoil] = great;
	lt[Plant::Pear][RockySoil] = poorly;
	lt[Plant::Pear][AridSoil] = rarely;
	lt[Plant::Pear][Oxisol] = poorly;
	lt[Plant::Pear][Gleysol] = poorly;


				// Olive Trees
				
	lt[Plant::Olive][Podzol] = rarely;
	lt[Plant::Olive][LoamSoil] = great;
	lt[Plant::Olive][PeatSoil] = rarely;
	lt[Plant::Olive][SandySoil] = optimal;
	lt[Plant::Olive][ClaySoil] = rarely;
	lt[Plant::Olive][SiltySoil] = great;
	lt[Plant::Olive][RockySoil] = good;
	lt[Plant::Olive][AridSoil] = optimal;
	lt[Plant::Olive][Oxisol] = poorly;
	lt[Plant::Olive][Gleysol] = rarely;				
				
							
// =========================
// BERRIES
// =========================

// Blueberry
	lt[Plant::Blueberry][Podzol] = great;
	lt[Plant::Blueberry][LoamSoil] = optimal;
	lt[Plant::Blueberry][PeatSoil] = great;
	lt[Plant::Blueberry][SandySoil] = good;
	lt[Plant::Blueberry][ClaySoil] = poorly;
	lt[Plant::Blueberry][SiltySoil] = great;
	lt[Plant::Blueberry][RockySoil] = rarely;
	lt[Plant::Blueberry][AridSoil] = rarely;
	lt[Plant::Blueberry][Oxisol] = poorly;
	lt[Plant::Blueberry][Gleysol] = good;


// Strawberry
	lt[Plant::Strawberry][Podzol] = good;
	lt[Plant::Strawberry][LoamSoil] = optimal;
	lt[Plant::Strawberry][PeatSoil] = good;
	lt[Plant::Strawberry][SandySoil] = great;
	lt[Plant::Strawberry][ClaySoil] = poorly;
	lt[Plant::Strawberry][SiltySoil] = great;
	lt[Plant::Strawberry][RockySoil] = rarely;
	lt[Plant::Strawberry][AridSoil] = rarely;
	lt[Plant::Strawberry][Oxisol] = poorly;
	lt[Plant::Strawberry][Gleysol] = good;


// =========================
// GRAPES
// =========================

	lt[Plant::Grapevine][Podzol] = rarely;
	lt[Plant::Grapevine][LoamSoil] = optimal;
	lt[Plant::Grapevine][PeatSoil] = good;
	lt[Plant::Grapevine][SandySoil] = great;
	lt[Plant::Grapevine][ClaySoil] = poorly;
	lt[Plant::Grapevine][SiltySoil] = great;
	lt[Plant::Grapevine][RockySoil] = good;
	lt[Plant::Grapevine][AridSoil] = good;
	lt[Plant::Grapevine][Oxisol] = poorly;
	lt[Plant::Grapevine][Gleysol] = rarely;


// =========================
// GRAINS
// =========================

// Wheat
	lt[Plant::Wheat][Podzol] = poorly;
	lt[Plant::Wheat][LoamSoil] = optimal;
	lt[Plant::Wheat][PeatSoil] = good;
	lt[Plant::Wheat][SandySoil] = good;
	lt[Plant::Wheat][ClaySoil] = good;
	lt[Plant::Wheat][SiltySoil] = good;
	lt[Plant::Wheat][RockySoil] = poorly;
	lt[Plant::Wheat][AridSoil] = poorly;
	lt[Plant::Wheat][Oxisol] = poorly;
	lt[Plant::Wheat][Gleysol] = rarely;


// Rice
	lt[Plant::Rice][Podzol] = poorly;
	lt[Plant::Rice][LoamSoil] = good;
	lt[Plant::Rice][PeatSoil] = great;
	lt[Plant::Rice][SandySoil] = poorly;
	lt[Plant::Rice][ClaySoil] = optimal;
	lt[Plant::Rice][SiltySoil] = optimal;
	lt[Plant::Rice][RockySoil] = poorly;
	lt[Plant::Rice][AridSoil] = poorly;
	lt[Plant::Rice][Oxisol] = poorly;
	lt[Plant::Rice][Gleysol] = great;

// Oat
	lt[Plant::Oat][Podzol] = rarely;
	lt[Plant::Oat][LoamSoil] = optimal;
	lt[Plant::Oat][PeatSoil] = good;
	lt[Plant::Oat][SandySoil] = great;
	lt[Plant::Oat][ClaySoil] = poorly;
	lt[Plant::Oat][SiltySoil] = good;
	lt[Plant::Oat][RockySoil] = good;
	lt[Plant::Oat][AridSoil] = good;
	lt[Plant::Oat][Oxisol] = poorly;
	lt[Plant::Oat][Gleysol] = rarely;


// =========================
// VEGETABLES
// =========================

// Lettuce
	lt[Plant::Lettuce][Podzol] = good;
	lt[Plant::Lettuce][LoamSoil] = optimal;
	lt[Plant::Lettuce][PeatSoil] = great;
	lt[Plant::Lettuce][SandySoil] = poorly;
	lt[Plant::Lettuce][ClaySoil] = good;
	lt[Plant::Lettuce][SiltySoil] = optimal;
	lt[Plant::Lettuce][RockySoil] = rarely;
	lt[Plant::Lettuce][AridSoil] = rarely;
	lt[Plant::Lettuce][Oxisol] = poorly;
	lt[Plant::Lettuce][Gleysol] = great;

// Kale
	lt[Plant::Kale][Podzol] = good;
	lt[Plant::Kale][LoamSoil] = optimal;
	lt[Plant::Kale][PeatSoil] = great;
	lt[Plant::Kale][SandySoil] = poorly;
	lt[Plant::Kale][ClaySoil] = good;
	lt[Plant::Kale][SiltySoil] = optimal;
	lt[Plant::Kale][RockySoil] = rarely;
	lt[Plant::Kale][AridSoil] = rarely;
	lt[Plant::Kale][Oxisol] = poorly;
	lt[Plant::Kale][Gleysol] = great;

// Carrot
	lt[Plant::Carrot][Podzol] = good;
	lt[Plant::Carrot][LoamSoil] = optimal;
	lt[Plant::Carrot][PeatSoil] = poorly;
	lt[Plant::Carrot][SandySoil] = great;
	lt[Plant::Carrot][ClaySoil] = poorly;
	lt[Plant::Carrot][SiltySoil] = good;
	lt[Plant::Carrot][RockySoil] = rarely;
	lt[Plant::Carrot][AridSoil] = rarely;
	lt[Plant::Carrot][Oxisol] = poorly;
	lt[Plant::Carrot][Gleysol] = rarely;


// Beets
	lt[Plant::Beets][Podzol] = good;
	lt[Plant::Beets][LoamSoil] = optimal;
	lt[Plant::Beets][PeatSoil] = poorly;
	lt[Plant::Beets][SandySoil] = great;
	lt[Plant::Beets][ClaySoil] = poorly;
	lt[Plant::Beets][SiltySoil] = good;
	lt[Plant::Beets][RockySoil] = rarely;
	lt[Plant::Beets][AridSoil] = rarely;
	lt[Plant::Beets][Oxisol] = poorly;
	lt[Plant::Beets][Gleysol] = rarely;


// Tubers 
	lt[Plant::Potato][Podzol] = good;
	lt[Plant::Potato][LoamSoil] = great;
	lt[Plant::Potato][PeatSoil] = poorly;
	lt[Plant::Potato][SandySoil] = optimal;
	lt[Plant::Potato][ClaySoil] = poorly;
	lt[Plant::Potato][SiltySoil] = good;
	lt[Plant::Potato][RockySoil] = rarely;
	lt[Plant::Potato][AridSoil] = rarely;
	lt[Plant::Potato][Oxisol] = poorly;
	lt[Plant::Potato][Gleysol] = rarely;


// Onion
	lt[Plant::Onion][Podzol] = good;
	lt[Plant::Onion][LoamSoil] = optimal;
	lt[Plant::Onion][PeatSoil] = poorly;
	lt[Plant::Onion][SandySoil] = great;
	lt[Plant::Onion][ClaySoil] = poorly;
	lt[Plant::Onion][SiltySoil] = good;
	lt[Plant::Onion][RockySoil] = rarely;
	lt[Plant::Onion][AridSoil] = rarely;
	lt[Plant::Onion][Oxisol] = poorly;
	lt[Plant::Onion][Gleysol] = rarely;


// Garlic 
	lt[Plant::Garlic][Podzol] = good;
	lt[Plant::Garlic][LoamSoil] = optimal;
	lt[Plant::Garlic][PeatSoil] = poorly;
	lt[Plant::Garlic][SandySoil] = great;
	lt[Plant::Garlic][ClaySoil] = poorly;
	lt[Plant::Garlic][SiltySoil] = good;
	lt[Plant::Garlic][RockySoil] = rarely;
	lt[Plant::Garlic][AridSoil] = rarely;
	lt[Plant::Garlic][Oxisol] = poorly;
	lt[Plant::Garlic][Gleysol] = rarely;


// Tomato
	lt[Plant::Tomato][Podzol] = good;
	lt[Plant::Tomato][LoamSoil] = optimal;
	lt[Plant::Tomato][PeatSoil] = poorly;
	lt[Plant::Tomato][SandySoil] = great;
	lt[Plant::Tomato][ClaySoil] = poorly;
	lt[Plant::Tomato][SiltySoil] = good;
	lt[Plant::Tomato][RockySoil] = rarely;
	lt[Plant::Tomato][AridSoil] = rarely;
	lt[Plant::Tomato][Oxisol] = poorly;
	lt[Plant::Tomato][Gleysol] = rarely;


// Cucumber
	lt[Plant::Cucumber][Podzol] = good;
	lt[Plant::Cucumber][LoamSoil] = optimal;
	lt[Plant::Cucumber][PeatSoil] = poorly;
	lt[Plant::Cucumber][SandySoil] = great;
	lt[Plant::Cucumber][ClaySoil] = poorly;
	lt[Plant::Cucumber][SiltySoil] = good;
	lt[Plant::Cucumber][RockySoil] = rarely;
	lt[Plant::Cucumber][AridSoil] = rarely;
	lt[Plant::Cucumber][Oxisol] = poorly;
	lt[Plant::Cucumber][Gleysol] = rarely;
	



// Pepper
	lt[Plant::Pepper][Podzol] = good;
	lt[Plant::Pepper][LoamSoil] = optimal;
	lt[Plant::Pepper][PeatSoil] = poorly;
	lt[Plant::Pepper][SandySoil] = great;
	lt[Plant::Pepper][ClaySoil] = poorly;
	lt[Plant::Pepper][SiltySoil] = good;
	lt[Plant::Pepper][RockySoil] = rarely;
	lt[Plant::Pepper][AridSoil] = rarely;
	lt[Plant::Pepper][Oxisol] = poorly;
	lt[Plant::Pepper][Gleysol] = rarely;



// =========================
// TEXTILE
// =========================

	lt[Plant::Cotton][Podzol] = poorly;
	lt[Plant::Cotton][LoamSoil] = optimal;
	lt[Plant::Cotton][PeatSoil] = poorly;
	lt[Plant::Cotton][SandySoil] = great;
	lt[Plant::Cotton][ClaySoil] = poorly;
	lt[Plant::Cotton][SiltySoil] = good;
	lt[Plant::Cotton][RockySoil] = rarely;
	lt[Plant::Cotton][AridSoil] = rarely;
	lt[Plant::Cotton][Oxisol] = poorly;
	lt[Plant::Cotton][Gleysol] = poorly;




	lt[Plant::Hemp][Podzol] = poorly;
	lt[Plant::Hemp][LoamSoil] = optimal;
	lt[Plant::Hemp][PeatSoil] = poorly;
	lt[Plant::Hemp][SandySoil] = great;
	lt[Plant::Hemp][ClaySoil] = poorly;
	lt[Plant::Hemp][SiltySoil] = good;
	lt[Plant::Hemp][RockySoil] = rarely;
	lt[Plant::Hemp][AridSoil] = rarely;
	lt[Plant::Hemp][Oxisol] = poorly;
	lt[Plant::Hemp][Gleysol] = poorly;



	lt[Plant::Flax][Podzol] = poorly;
	lt[Plant::Flax][LoamSoil] = optimal;
	lt[Plant::Flax][PeatSoil] = poorly;
	lt[Plant::Flax][SandySoil] = great;
	lt[Plant::Flax][ClaySoil] = poorly;
	lt[Plant::Flax][SiltySoil] = good;
	lt[Plant::Flax][RockySoil] = rarely;
	lt[Plant::Flax][AridSoil] = rarely;
	lt[Plant::Flax][Oxisol] = poorly;
	lt[Plant::Flax][Gleysol] = poorly;





// =========================
// FERNS
// =========================

	lt[Plant::Fern][Podzol] = great;
	lt[Plant::Fern][LoamSoil] = optimal;
	lt[Plant::Fern][PeatSoil] = optimal;
	lt[Plant::Fern][SandySoil] = poorly;
	lt[Plant::Fern][ClaySoil] = rarely;
	lt[Plant::Fern][SiltySoil] = great;
	lt[Plant::Fern][RockySoil] = rarely;
	lt[Plant::Fern][Oxisol] = poorly;
	lt[Plant::Fern][Gleysol] = great;



// =========================
// REEDS
// =========================

	lt[Plant::Reed][Podzol] = good;
	lt[Plant::Reed][LoamSoil] = great;
	lt[Plant::Reed][PeatSoil] = optimal;
	lt[Plant::Reed][SandySoil] = poorly;
	lt[Plant::Reed][ClaySoil] = good;
	lt[Plant::Reed][SiltySoil] = great;
	lt[Plant::Reed][RockySoil] = poorly;
	lt[Plant::Reed][Oxisol] = poorly;
	lt[Plant::Reed][Gleysol] = optimal;

	return lt;
}();

inline constexpr LookupTable<Biome, float> coverages = []
{
	LookupTable<Biome, float> lt{};
	using enum Biome;
	lt[HotDesert] = 0.08;
	lt[Grassland] = 0.2;
	lt[Savanna] = 0.25;
	lt[Wetland] = 0.43;
	lt[Temperate] = 0.89;
	lt[Boreal] = 0.79;
	lt[Jungle] = 0.98;
	lt[Rocky] = 0.17;
	lt[Tundra] = 0.15;
	lt[ColdDesert] = 0.08;
	return lt;
}();
}; //namespace plant
