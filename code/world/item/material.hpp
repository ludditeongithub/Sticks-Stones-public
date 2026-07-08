#ifndef MATERIALS_H_
#define MATERIALS_H_

#include <world/item/enum.hpp>
#include <core/tables.hpp>

inline constexpr LookupTable<Material,float>  weightMultiplier = [] {
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

inline constexpr LookupTable<Material,float> toughnessMultiplier = [] {
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

void intializeToughnessMultipliers()
{
	
}

// float durabilityMultiplier[static_cast<int>(Material::MAX)];

// void initializeDurabilityMultipliers() {
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

float hardnessMultiplier[static_cast<int>(Material::MAX)];

void initializeHardnessMultipliers()
{
	hardnessMultiplier[static_cast<int>(Material::Wood)] = 1.2;
	hardnessMultiplier[static_cast<int>(Material::Bone)] = 5.0;
	hardnessMultiplier[static_cast<int>(Material::Stone)] = 3.5;
	hardnessMultiplier[static_cast<int>(Material::Copper)] = 3;
	hardnessMultiplier[static_cast<int>(Material::Bronze)] = 3;
	hardnessMultiplier[static_cast<int>(Material::Iron)] = 4.2;
	hardnessMultiplier[static_cast<int>(Material::Steel)] = 4.5;
	hardnessMultiplier[static_cast<int>(Material::Silver)] = 2.5;
	hardnessMultiplier[static_cast<int>(Material::Gold)] = 2.5;
}

float brittlenessMultiplier[static_cast<int>(Material::MAX)];

void initializeBrittlenessMultipliers()
{
	brittlenessMultiplier[static_cast<int>(Material::Wood)] = 3.2;
	brittlenessMultiplier[static_cast<int>(Material::Bone)] = 6.0;
	brittlenessMultiplier[static_cast<int>(Material::Stone)] = 4.5;
	brittlenessMultiplier[static_cast<int>(Material::Copper)] = 0.15;
	brittlenessMultiplier[static_cast<int>(Material::Bronze)] = 0.3;
	brittlenessMultiplier[static_cast<int>(Material::Iron)] = 0.5;
	brittlenessMultiplier[static_cast<int>(Material::Steel)] = 0.4;
	brittlenessMultiplier[static_cast<int>(Material::Silver)] = 0.4;
	brittlenessMultiplier[static_cast<int>(Material::Gold)] = 0.8;
}

// TODO: custom durability multipliers for some items

float sharpnessMultiplier[static_cast<int>(Material::MAX)];

void initializeSharpnessMultipliers()
{
	sharpnessMultiplier[static_cast<int>(Material::Wood)] = 0.5;
	sharpnessMultiplier[static_cast<int>(Material::Bone)] = 0.7;
	sharpnessMultiplier[static_cast<int>(Material::Stone)] = 0.8;
	sharpnessMultiplier[static_cast<int>(Material::Copper)] = 0.65;
	sharpnessMultiplier[static_cast<int>(Material::Bronze)] = 1.55;
	sharpnessMultiplier[static_cast<int>(Material::Iron)] = 1.15;
	sharpnessMultiplier[static_cast<int>(Material::Steel)] = 2.2;
	sharpnessMultiplier[static_cast<int>(Material::Silver)] = 0.25;
	sharpnessMultiplier[static_cast<int>(Material::Gold)] = 0.25;
}

beautyMultiplier

#endif // MATERIALS_H_
