#ifndef MATERIALS_H_
#define MATERIALS_H_

#include <data/types/item.hpp>
#include <core/tables.hpp>

inline constexpr LookupTable<Material,float>  WEIGHT_MULTIPLIER = [] {
  LookupTable<Material,float> lt{};
  using enum Material;
  	lt[Material::Wood] = 0.7;
	lt[Material::Bone] = 0.8;
	lt[Material::Leather] = 0.6;
	lt[Material::Stone] = 1.4;
	lt[Material::Copper] = 3.8;
	lt[Material::Bronze] = 3.9;
	lt[Material::Iron] = 4.4;
	lt[Material::Steel] = 4.45;
	lt[Material::Silver] = 5.2;
	lt[Material::Gold] = 5.7;
  return lt;
 }();

inline constexpr LookupTable<Material,float> TOUGHNESS_MULTIPLIER = [] {
  LookupTable<Material,float> lt{};
  using enum Material;
    lt[Material::Wood] = 4.0;
	lt[Material::Bone] = 6.0;
	lt[Material::Leather] = 14.0;
	lt[Material::Stone] = 16.0;
	lt[Material::Copper] = 18.0;
	lt[Material::Bronze] = 35.0;
	lt[Material::Iron] = 30.0;
	lt[Material::Steel] = 52.0;
	lt[Material::Silver] = 19.0;
	lt[Material::Gold] = 22.0;
  return lt;
 }();

inline constexpr LookupTable<Material,float> DURABILITY_MULTIPLIERS = [] {
		LookupTable<Material,float> lt{};
		using enum Material;
		
		return lt;
}();

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

inline constexpr LookupTable<Material,float> HARDNESS_MULTIPLIERS = [] {
		LookupTable<Material,float> lt{};
		using enum Material;
		lt[(Material::Wood)] = 1.2;
	lt[(Material::Bone)] = 5.0;
	lt[(Material::Stone)] = 3.5;
	lt[(Material::Copper)] = 3;
	lt[(Material::Bronze)] = 3;
	lt[(Material::Iron)] = 4.2;
	lt[(Material::Steel)] = 4.5;
	lt[(Material::Silver)] = 2.5;
	lt[(Material::Gold)] = 2.5;
		return lt;
}();

inline constexpr LookupTable<Material,float> BRITTLENESS_MULTIPLIERS = [] {
		LookupTable<Material,float> lt{};
		using enum Material;
		lt[(Material::Wood)] = 3.2;
	lt[(Material::Bone)] = 6.0;
	lt[(Material::Stone)] = 4.5;
	lt[(Material::Copper)] = 0.15;
	lt[(Material::Bronze)] = 0.3;
	lt[(Material::Iron)] = 0.5;
	lt[(Material::Steel)] = 0.4;
	lt[(Material::Silver)] = 0.4;
	lt[(Material::Gold)] = 0.8;
		return lt;
}();


// TODO: custom durability multipliers for some items

inline constexpr LookupTable<Material,float> SHARPNESS_MULTIPLIERS = [] {
		LookupTable<Material,float> lt{};
		using enum Material;
		lt[(Material::Wood)] = 0.5;
	lt[(Material::Bone)] = 0.7;
	lt[(Material::Stone)] = 0.8;
	lt[(Material::Copper)] = 0.65;
	lt[(Material::Bronze)] = 1.55;
	lt[(Material::Iron)] = 1.15;
	lt[(Material::Steel)] = 2.2;
	lt[(Material::Silver)] = 0.25;
	lt[(Material::Gold)] = 0.25;
		return lt;
}();

inline constexpr LookupTable<Material,float> BEAUTY_MULTIPLIERS = [] {
		LookupTable<Material,float> lt{};
		using enum Material;
		
		return lt;
}();

#endif // MATERIALS_H_
