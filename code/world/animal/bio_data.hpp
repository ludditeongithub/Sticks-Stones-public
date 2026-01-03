#ifndef LIFESTATS_HPP
#define LIFESTATS_HPP

#include <basic/struct.hpp>
#include "enum.hpp"

namespace animal {

inline constexpr LookupTable<Type, float> fertilityAge = [] {
    LookupTable<Type, float> arr;
    arr[Type::Pig] = 0.5f;
    arr[Type::Cow] = 1.5f;
    arr[Type::Chicken] = 0.3f;
    arr[Type::Duck] = 0.4f;
    arr[Type::Sheep] = 1.0f;
    arr[Type::Goat] = 1.0f;
    arr[Type::Horse] = 3.0f;
    arr[Type::Ox] = 2.0f;
    arr[Type::Donkey] = 2.0f;
    arr[Type::Camel] = 4.0f;
    arr[Type::WaterBuffalo] = 3.0f;
    arr[Type::Rabbit] = 0.3f;
    arr[Type::Antelope] = 1.5f;
    arr[Type::Deer] = 1.5f;
    arr[Type::Moose] = 2.0f;
    arr[Type::Capybara] = 1.0f;
    arr[Type::Turtle] = 10.0f;
    arr[Type::Elephant] = 10.0f;
    arr[Type::Bison] = 2.5f;
    arr[Type::Wolf] = 2.0f;
    arr[Type::Bear] = 3.0f;
    arr[Type::Caribou] = 2.0f;
    arr[Type::Fish] = 1.0f;

    return arr;
}();


inline constexpr LookupTable<Type, float>
    estimatedLifespan = [] {
      LookupTable<Type, float> arr;

      arr[Type::Pig] = 15.0f;
      arr[Type::Cow] = 20.0f;
      arr[Type::Chicken] = 8.0f;
      arr[Type::Duck] = 10.0f;
      arr[Type::Sheep] = 12.0f;
      arr[Type::Goat] = 15.0f;
      arr[Type::Horse] = 30.0f;
      arr[Type::Ox] = 20.0f;
      arr[Type::Donkey] = 30.0f;
      arr[Type::Camel] = 40.0f;
      arr[Type::WaterBuffalo] = 25.0f;
      arr[Type::Rabbit] = 9.0f;
      arr[Type::Antelope] = 12.0f;
      arr[Type::Deer] = 15.0f;
      arr[Type::Moose] = 20.0f;
      arr[Type::Capybara] = 10.0f;
      arr[Type::Turtle] = 80.0f;
      arr[Type::Elephant] = 70.0f;
      arr[Type::Bison] = 20.0f;
      arr[Type::Wolf] = 13.0f;
      arr[Type::Bear] = 25.0f;
      arr[Type::Caribou] = 15.0f;
      arr[Type::Fish] = 5.0f;

      return arr;
    }();

  inline constexpr LookupTable<float, uint16> maxHunger = [] {
    LookupTable<Type,uint16_t> arr;
  
  return arr;
 }();  

  inline constexpr LookupTable<Type, uint16_t)> sightRanges = [] {
    LookupTable<Type, uint16_t> arr;

    arr[Type::Pig] = 50;
    arr[Type::Cow] = 150;
    arr[Type::Chicken] = 30;
    arr[Type::Duck] = 80;
    arr[Type::Sheep] = 200;
    arr[Type::Goat] = 250;
    arr[Type::Horse] = 300;
    arr[Type::Ox] = 150;
    arr[Type::Donkey] = 200;
    arr[Type::Camel] = 500;
    arr[Type::WaterBuffalo] = 100;
    arr[Type::Rabbit] = 100;
    arr[Type::Antelope] = 600;
    arr[Type::Deer] = 500;
    arr[Type::Moose] = 300;
    arr[Type::Capybara] = 80;
    arr[Type::Turtle] = 30;
    arr[Type::Elephant] = 200;
    arr[Type::Bison] = 300;
    arr[Type::Wolf] = 1000;
    arr[Type::Bear] = 400;
    arr[Type::Caribou] = 600;
    arr[Type::Fish] = 20;

    return arr;
}();

inline constexpr LookupTable<Type, float> minSpeed = [] {
  LookupTable<Type, float> arr;

    arr[Type::Pig] = 1.5f;
    arr[Type::Cow] = 1.0f;
    arr[Type::Chicken] = 0.8f;
    arr[Type::Duck] = 0.8f;
    arr[Type::Sheep] = 1.0f;
    arr[Type::Goat] = 1.0f;
    arr[Type::Horse] = 1.6f;
    arr[Type::Ox] = 1.0f;
    arr[Type::Donkey] = 1.2f;
    arr[Type::Camel] = 1.3f;
    arr[Type::WaterBuffalo] = 0.9f;
    arr[Type::Rabbit] = 1.0f;
    arr[Type::Antelope] = 2.0f;
    arr[Type::Deer] = 1.8f;
    arr[Type::Moose] = 1.2f;
    arr[Type::Capybara] = 0.8f;
    arr[Type::Turtle] = 0.05f;
    arr[Type::Elephant] = 1.5f;
    arr[Type::Bison] = 1.5f;
    arr[Type::Wolf] = 1.8f;
    arr[Type::Bear] = 1.3f;
    arr[Type::Caribou] = 1.8f;
    arr[Type::Fish] = 0.5f;

    return arr;
}();


inline constexpr LookupTable<Type, float> maxSpeed = [] {
    LookupTable<Type, float> arr;

    arr[Type::Pig] = 6.0f;
    arr[Type::Cow] = 7.5f;
    arr[Type::Chicken] = 4.0f;
    arr[Type::Duck] = 10.0f;
    arr[Type::Sheep] = 14.0f;
    arr[Type::Goat] = 12.0f;
    arr[Type::Horse] = 22.0f;
    arr[Type::Ox] = 5.5f;
    arr[Type::Donkey] = 8.3f;
    arr[Type::Camel] = 14.0f;
    arr[Type::WaterBuffalo] = 5.0f;
    arr[Type::Rabbit] = 17.0f;
    arr[Type::Antelope] = 27.0f;
    arr[Type::Deer] = 22.0f;
    arr[Type::Moose] = 15.0f;
    arr[Type::Capybara] = 8.3f;
    arr[Type::Turtle] = 0.3f;
    arr[Type::Elephant] = 6.8f;
    arr[Type::Bison] = 18.0f;
    arr[Type::Wolf] = 17.0f;
    arr[Type::Bear] = 13.4f;
    arr[Type::Caribou] = 20.0f;
    arr[Type::Fish] = 8.0f;

    return arr;
}();

inline constexpr BitsetTable<Type> isEggLayer =
[] {
    BitsetTable<Type> b;
    b.set(Type::Chicken);
    b.set(Type::Duck);
    b.set(Type::Turtle);
    b.set(Type::Fish);
    return b;
}();


}

#endif
