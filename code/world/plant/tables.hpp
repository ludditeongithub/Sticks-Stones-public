#pragma once
#include "enum.hpp"
#include <world/world.hpp>
#include <core/containers.hpp>
#include <array>
#include <core/data.hpp>

using enum Plant;

  constexpr float UNOPTIMAL_TEMP_MULT = 0.65;
  constexpr float LOW_WATER_MULT = 0.55;
  
  //TODO: manage sunlight and sun values
  
  //TODO: change these all to uint16_ts
  inline constexpr LookupTable<Plant, float> waterDeathMin = [] {
    LookupTable<Plant, float> arr{};
    arr[Wheat] = 8.0;
    arr[Oat] = 8.0;
    arr[Corn] = 12.0;
    arr[Tomato] = 8.0;
    arr[Rice] = 8.0;
    arr[Onion] = 6.0;
    arr[Cabbage] = 6.0;
    arr[Pepper] = 8.0;
    arr[Potato] = 9.0;
    arr[Carrot] = 8.0;
    arr[Poppy] = 8.0;
    arr[Senna] = 8.5;
    arr[Cotton] = 15.5;
    arr[Papyrus] = 16.5;
    arr[Flax] = 8.0;
    arr[Hemp] = 9.5;
    arr[Lettuce] = 6.5;
    return arr;
  }();

  inline constexpr LookupTable<Plant, float> waterDeath = [] {
      LookupTable<Plant, float> arr{};
      arr[Wheat] = HOUR_LENGTH * 70;
      arr[Oat] = HOUR_LENGTH * 42;
      arr[Corn] = HOUR_LENGTH * 36;
      arr[Tomato] = HOUR_LENGTH * 20;
      arr[Rice] = HOUR_LENGTH * 20;
      arr[Onion] = HOUR_LENGTH * 36;
      arr[Cabbage] = HOUR_LENGTH * 36;
      arr[Pepper] = HOUR_LENGTH * 20;
      arr[Potato] = HOUR_LENGTH * 28;
      arr[Carrot] = HOUR_LENGTH * 30;
      arr[Poppy] = HOUR_LENGTH * 29;
      arr[Senna] = HOUR_LENGTH * 68;
      arr[Cotton] = HOUR_LENGTH * 104;
      arr[Papyrus] = HOUR_LENGTH * 1;
      arr[Flax] = HOUR_LENGTH * 30;
      arr[Hemp] = HOUR_LENGTH * 52;
      arr[Lettuce] = HOUR_LENGTH * 20; 
      return arr;
    }();  

 //  inline constexpr LookupTable<Plant, float> waterDeathMax = [] {
 //  LookupTable<Plant, float> arr{};
 //  arr[Oat] = 250.0;
 //  arr[Wheat] =  250.0;
 //  arr[Corn] = 250.0;
 //  arr[Tomato] = 180.0;
 //  arr[Onion] = 200.0;
 //  arr[Rice] = 200.0;
 //  arr[Cabbage] = 200.0;
 //  arr[Pepper] = 220.0;
 //  arr[Potato] = 220.0;
 //  arr[Carrot] = 180.0;
 //  arr[Poppy] = 200.0;
 //  arr[Senna] = 220.0;
 //  arr[Cotton] = 250.0;
 //  arr[Papyrus] = 260.0;
 //  arr[Flax] = 220.0;
 //  arr[Hemp] = 250.0;
 //  arr[Lettuce] = 150.0; 
 //  return arr;
 // }();

inline constexpr LookupTable<Plant, float> waterRequired = [] {
  LookupTable<Plant, float> arr{};
    arr[Wheat] = 750.0 / DAY_LENGTH;
    arr[Oat] = 650.0 / DAY_LENGTH;
    arr[Corn] = 1250.0 / DAY_LENGTH;
    arr[Tomato] = 750.0 / DAY_LENGTH;
    arr[Rice] = 1750.0 / DAY_LENGTH;
    arr[Onion] = 450.0 / DAY_LENGTH;
    arr[Cabbage] = 600.0 / DAY_LENGTH;
    arr[Pepper] = 450.0 / DAY_LENGTH;
    arr[Potato] = 750.0 / DAY_LENGTH;
    arr[Carrot] = 600.0 / DAY_LENGTH;
    arr[Poppy] = 450.0 / DAY_LENGTH;
    arr[Senna] = 300.0 / DAY_LENGTH;
    arr[Cotton] = 800.0 / DAY_LENGTH;
    arr[Papyrus] = 1500.0 / DAY_LENGTH;
    arr[Flax] = 600.0 / DAY_LENGTH;
    arr[Hemp] = 750.0 / DAY_LENGTH;
    arr[Lettuce] = 400.0 / DAY_LENGTH; 
  return arr;
}();

inline constexpr LookupTable<Plant, float> tempDeathMin = [] {
    LookupTable<Plant, float> arr{};
    arr[Wheat] = -10.0;
    arr[Oat] = -8.0;
    arr[Corn] = 0.0;
    arr[Tomato] = 0.0;
    arr[Rice] = 6.0;
    arr[Onion] = -5.0;
    arr[Cabbage] = -5.0;
    arr[Pepper] = 5.0;
    arr[Potato] = -2.0;
    arr[Carrot] = -6.0;
    arr[Poppy] = -5.0;
    arr[Senna] = 0.0;
    arr[Cotton] = 0.0;
    arr[Papyrus] = 0.0;
    arr[Flax] = -5.0;
    arr[Hemp] = -5.0;
    arr[Lettuce] = 0.0; 
    return arr;
}();

  //TODO : change these to int16_ts?
inline constexpr LookupTable<Plant, float> tempDeathMax = [] {
  LookupTable<Plant, float> arr{};
  arr[Wheat] =  42.0;
  arr[Oat] = 42.0;
  arr[Corn] = 45.0;
  arr[Rice] = 45.0;
  arr[Tomato] = 40.0;
  arr[Onion] = 40.0;
  arr[Cabbage] = 40.0;
  arr[Pepper] = 40.0;
  arr[Potato] = 40.0;
  arr[Carrot] = 40.0;
  arr[Poppy] = 40.0;
  arr[Senna] = 45.0;
  arr[Cotton] = 45.0;
  arr[Papyrus] = 45.0;
  arr[Flax] = 40.0;
  arr[Hemp] = 40.0;
  arr[Lettuce] = 32.0; 
    return arr;
 }();


inline constexpr LookupTable<Plant, float> tempOptimalMin = [] {
  LookupTable<Plant, float> arr{};
  arr[Oat] = 14.0;
  arr[Wheat] =  14.0;
  arr[Corn] = 16.0;
  arr[Tomato] = 18.0;
  arr[Onion] = 12.0;
  arr[Rice] = 20.0;
  arr[Cabbage] = 15.0;
  arr[Pepper] = 18.0;
  arr[Potato] = 13.0;
  arr[Carrot] = 12.0;
  arr[Poppy] = 10.0;
  arr[Senna] = 15.0;
  arr[Cotton] = 18.0;
  arr[Papyrus] = 15.0;
  arr[Flax] = 10.0;
  arr[Hemp] = 15.0;
  arr[Lettuce] = 16.0; 
  return arr;
 }();

inline constexpr LookupTable<Plant, float> tempOptimalMax = [] {
  LookupTable<Plant, float> arr{};
  arr[Oat] = 21.0;
  arr[Wheat] =  21.0;
  arr[Corn] = 28.0;
  arr[Rice] = 35.0;
  arr[Tomato] = 30.0;
  arr[Onion] = 25.0;
  arr[Cabbage] = 28.0;
  arr[Pepper] = 28.0;
  arr[Potato] = 27.0;
  arr[Carrot] = 25.0;
  arr[Poppy] = 25.0;
  arr[Senna] = 35.0;
  arr[Cotton] = 32.0;
  arr[Papyrus] = 32.0;
  arr[Flax] = 22.0;
  arr[Hemp] = 30.0;
  arr[Lettuce] = 21.0; 
  return arr;
 }();

  
inline constexpr LookupTable<Plant, float> tempGrowthMin = [] {
  LookupTable<Plant, float> arr{};
  arr[Oat] = 4.0; 
  arr[Wheat] =  4.0;
  arr[Corn] = 10.0;
  arr[Tomato] = 10.0;
  arr[Rice] = 15.0;
  arr[Onion] = 5.0;
  arr[Cabbage] = 5.0;
  arr[Pepper] = 10.0;
  arr[Potato] = 6.0;
  arr[Carrot] = 5.0;
  arr[Poppy] = 5.0;
  arr[Senna] = 5.0;
  arr[Cotton] = 10.0;
  arr[Papyrus] = 20.0;
  arr[Flax] = 4.0;
  arr[Hemp] = 10.0;
  arr[Lettuce] = 7.0; 
  return arr;
 }();


inline constexpr LookupTable<Plant, float> tempGrowthMax = [] {
  LookupTable<Plant, float> arr{};
  arr[Oat] = 38.0;
  arr[Wheat] =  38.0;
  arr[Corn] = 40.0;
  arr[Tomato] = 35.0;
  arr[Onion] = 30.0;
  arr[Rice] = 40.0;
  arr[Cabbage] = 40.0;
  arr[Pepper] = 35.0;
  arr[Potato] = 32.0;
  arr[Carrot] = 30.0;
  arr[Poppy] = 30.0;
  arr[Senna] = 30.0;
  arr[Cotton] = 35.0;
  arr[Papyrus] = 35.0;
  arr[Flax] = 35.0;
  arr[Hemp] = 35.0;
  arr[Lettuce] = 24.0; 
  return arr;
 }();
  
  
inline constexpr LookupTable<Plant, Time> fullyGrownAmt = [] {
  LookupTable<Plant, Time> arr{};
  arr[Corn] = 34125.0;
  arr[Rice] = 29250.0;
  arr[Wheat] =  29250.0;
  arr[Tomato] = 25312.5;
  arr[Onion] = 27787.5;
  arr[Cabbage] = 33750.0;
  arr[Pepper] = 28125.0;
  arr[Potato] = 24318.0;
  arr[Carrot] = 25312.5;
  arr[Poppy] = 25312.5;
  arr[Senna] = 29250.0;
  arr[Cotton] = 42187.0;
  arr[Papyrus] = 42187.0;
  arr[Flax] = 33750.0;
  arr[Hemp] = 36562.5;
  arr[Lettuce] = 25312.5; 
  return arr;
 }();


inline constexpr LookupTable<Plant, int> harvestAmt = [] {
  LookupTable<Plant, int> arr{};
  arr[Wheat] = 30;
  arr[Oat] = 30;
  arr[Corn] = 30;
  arr[Rice] = 30;
  arr[Tomato] = 30;
  arr[Onion] = 30;
  arr[Potato] = 30;
  arr[Cabbage] = 30;
  arr[Pepper] = 30;
  arr[Carrot] = 30;
  arr[Poppy] = 30;
  arr[Senna] = 30;
  arr[Cotton] = 30;
  arr[Papyrus] = 30;
  arr[Flax] = 30;
  arr[Hemp] = 30;
  arr[Lettuce] = 30; 
  return arr;
}();

inline constexpr LookupTable<Plant, bool> requiresScythe = [] {
  LookupTable<Plant, bool> arr{};
  arr[Wheat] = true;
  arr[Oat] = true;
  arr[Corn] = true;
  arr[Rice] = true;
  arr[Tomato] = false;
  arr[Onion] = false;
  arr[Potato] = false;
  arr[Cabbage] = true;
  arr[Pepper] = true;
  arr[Carrot] = true;
  arr[Poppy] = true;
  arr[Senna] = true;
  arr[Cotton] = true;
  arr[Papyrus] = true;
  arr[Flax] = true;
  arr[Hemp] = true;
  arr[Lettuce] = false;
  return arr;
}();

// TODO
inline constexpr LookupTable<Plant,float> perfectSunlight = [] {
  LookupTable<Plant,float> lt{};
  using enum Plant;
  lt[Wheat] = true;
  lt[Oat] = true;
  lt[Corn] = true;
  lt[Rice] = true;
  lt[Tomato] = false;
  lt[Onion] = false;
  lt[Potato] = false;
  lt[Cabbage] = true;
  lt[Pepper] = true;
  lt[Carrot] = true;
  lt[Poppy] = true;
  lt[Senna] = true;
  lt[Cotton] = true;
  lt[Papyrus] = true;
  lt[Flax] = true;
  lt[Hemp] = true;
  lt[Lettuce] = false;
  return lt;
 }();
