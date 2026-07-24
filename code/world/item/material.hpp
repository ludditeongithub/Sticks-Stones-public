#ifndef MATERIALS_H_
#define MATERIALS_H_

#include <world/item/enum.hpp>
#include <core/tables.hpp>

inline constexpr LookupTable<Material,float>  weight_multiplier = [] {
  LookupTable<Material,float> lt{};
  using enum Material;
  	lt[static_cast<int>(Material::Wood)] = 0.7;
	lt[static_cast<int>(Material::Bone)] = 0.8;
	lt[static_cast<int>(Material::Leather)] = 0.6;
	lt[static_cast<int>(Material::Stone)] = 1.4;
	lt[static_cast<int>(Material::Copper)] = 3.8;
	lt[static_cast<int>(Material::Bronze)] = 3.9;
	lt[static_cast<int>(Material::Iron)] = 4.4;
	lt[static_cast<int>(Material::Steel)] = 4.45;
	lt[static_cast<int>(Material::Silver)] = 5.2;
	lt[static_cast<int>(Material::Gold)] = 5.7;
  return lt;
 }();

inline constexpr LookupTable<Material,float> toughness_multiplier = [] {
  LookupTable<Material,float> lt{};
  using enum Material;
        lt[static_cast<int>(Material::Wood)] = 4.0;
	lt[static_cast<int>(Material::Bone)] = 6.0;
	lt[static_cast<int>(Material::Leather)] = 14.0;
	lt[static_cast<int>(Material::Stone)] = 16.0;
	lt[static_cast<int>(Material::Copper)] = 18.0;
	lt[static_cast<int>(Material::Bronze)] = 35.0;
	lt[static_cast<int>(Material::Iron)] = 30.0;
	lt[static_cast<int>(Material::Steel)] = 52.0;
	lt[static_cast<int>(Material::Silver)] = 19.0;
	lt[static_cast<int>(Material::Gold)] = 22.0;
  return lt;
 }();

float lt[static_cast<int>(Material::MAX)];

void intialize_toughness_multipliers()
{
	
}

// float durability_multiplier[static_cast<int>(Material::MAX)];

// void initialize_durability_multipliers() {
//     Wood 0.4
//     Bone 0.6
//     Stone 0.8
//     Copper 0.5
//     Bronze 2.9
//     Iron 2.2
//     Steel 5.4
//     Silver 0.4
//     Gold 0.2
//  }

float hardness_multiplier[static_cast<int>(Material::MAX)];

void initialize_hardness_multipliers()
{
	hardness_multiplier[static_cast<int>(Material::Wood)] = 1.2;
	hardness_multiplier[static_cast<int>(Material::Bone)] = 5.0;
	hardness_multiplier[static_cast<int>(Material::Stone)] = 3.5;
	hardness_multiplier[static_cast<int>(Material::Copper)] = 3;
	hardness_multiplier[static_cast<int>(Material::Bronze)] = 3;
	hardness_multiplier[static_cast<int>(Material::Iron)] = 4.2;
	hardness_multiplier[static_cast<int>(Material::Steel)] = 4.5;
	hardness_multiplier[static_cast<int>(Material::Silver)] = 2.5;
	hardness_multiplier[static_cast<int>(Material::Gold)] = 2.5;
}

float brittleness_multiplier[static_cast<int>(Material::MAX)];

void initialize_brittleness_multipliers()
{
	brittleness_multiplier[static_cast<int>(Material::Wood)] = 3.2;
	brittleness_multiplier[static_cast<int>(Material::Bone)] = 6.0;
	brittleness_multiplier[static_cast<int>(Material::Stone)] = 4.5;
	brittleness_multiplier[static_cast<int>(Material::Copper)] = 0.15;
	brittleness_multiplier[static_cast<int>(Material::Bronze)] = 0.3;
	brittleness_multiplier[static_cast<int>(Material::Iron)] = 0.5;
	brittleness_multiplier[static_cast<int>(Material::Steel)] = 0.4;
	brittleness_multiplier[static_cast<int>(Material::Silver)] = 0.4;
	brittleness_multiplier[static_cast<int>(Material::Gold)] = 0.8;
}

// TODO: custom durability multipliers for some items

float sharpness_multiplier[static_cast<int>(Material::MAX)];

void initialize_sharpness_multipliers()
{
	sharpness_multiplier[static_cast<int>(Material::Wood)] = 0.5;
	sharpness_multiplier[static_cast<int>(Material::Bone)] = 0.7;
	sharpness_multiplier[static_cast<int>(Material::Stone)] = 0.8;
	sharpness_multiplier[static_cast<int>(Material::Copper)] = 0.65;
	sharpness_multiplier[static_cast<int>(Material::Bronze)] = 1.55;
	sharpness_multiplier[static_cast<int>(Material::Iron)] = 1.15;
	sharpness_multiplier[static_cast<int>(Material::Steel)] = 2.2;
	sharpness_multiplier[static_cast<int>(Material::Silver)] = 0.25;
	sharpness_multiplier[static_cast<int>(Material::Gold)] = 0.25;
}

beauty_multiplier

#endif // MATERIALS_H_
