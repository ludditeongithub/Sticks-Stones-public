#ifndef LIFESTATS_HPP
#define LIFESTATS_HPP

#include "enum.hpp"
#include <core/tables.hpp>
#include <core/data.hpp>
#include <core/time.hpp>

inline constexpr LookupTable<Animal, Time> fertilityAge = [] {
    LookupTable<Animal, Time> arr;
    arr[Animal::Pig] = static_cast<int>(0.5 * YEAR_LENGTH);
    arr[Animal::Cow] = static_cast<int>(1.5 * YEAR_LENGTH);
    arr[Animal::Chicken] = static_cast<int>(0.3 * YEAR_LENGTH);
    arr[Animal::Duck] = static_cast<int>(0.4 * YEAR_LENGTH);
    arr[Animal::Sheep] = static_cast<int>(1.0 * YEAR_LENGTH);
    arr[Animal::Goat] = static_cast<int>(1.0 * YEAR_LENGTH);
    arr[Animal::Horse] = static_cast<int>(3.0 * YEAR_LENGTH);
    arr[Animal::Ox] = static_cast<int>(2.0 * YEAR_LENGTH);
    arr[Animal::Donkey] = static_cast<int>(2.0 * YEAR_LENGTH);
    arr[Animal::Camel] = static_cast<int>(4.0 * YEAR_LENGTH);
    arr[Animal::WaterBuffalo] = static_cast<int>(3.0 * YEAR_LENGTH);
    arr[Animal::Rabbit] = static_cast<int>(0.3 * YEAR_LENGTH);
    arr[Animal::Antelope] = static_cast<int>(1.5 * YEAR_LENGTH);
    arr[Animal::Deer] = static_cast<int>(1.5 * YEAR_LENGTH);
    arr[Animal::Moose] = static_cast<int>(2.0 * YEAR_LENGTH);
    arr[Animal::Capybara] = static_cast<int>(1.0 * YEAR_LENGTH);
    arr[Animal::Turtle] = static_cast<int>(10.0 * YEAR_LENGTH);
    arr[Animal::Elephant] = static_cast<int>(10.0 * YEAR_LENGTH);
    arr[Animal::Bison] = static_cast<int>(2.5 * YEAR_LENGTH);
    arr[Animal::Wolf] = static_cast<int>(2.0 * YEAR_LENGTH);
    arr[Animal::Bear] = static_cast<int>(3.0 * YEAR_LENGTH);
    arr[Animal::Caribou] = static_cast<int>(2.0 * YEAR_LENGTH);
    arr[Animal::Fish] = static_cast<int>(1.0 * YEAR_LENGTH);

    return arr;
}();


inline constexpr LookupTable<Animal, Time> estimatedLifespan = [] {
  LookupTable<Animal, Time> arr;

  arr[Animal::Pig] =   static_cast<int>(15.0 * YEAR_LENGTH);
  arr[Animal::Cow] = static_cast<int>(20.0 * YEAR_LENGTH);
  arr[Animal::Chicken] = static_cast<int>(8.0 * YEAR_LENGTH);
  arr[Animal::Duck] = static_cast<int>(10.0 * YEAR_LENGTH);
  arr[Animal::Sheep] = static_cast<int>(12.0 * YEAR_LENGTH);
  arr[Animal::Goat] = static_cast<int>(15.0 * YEAR_LENGTH);
  arr[Animal::Horse] = static_cast<int>(30.0 * YEAR_LENGTH);
  arr[Animal::Ox] = static_cast<int>(20.0 * YEAR_LENGTH);
  arr[Animal::Donkey] = static_cast<int>(30.0 * YEAR_LENGTH);
  arr[Animal::Camel] = static_cast<int>(40.0 * YEAR_LENGTH);
  arr[Animal::WaterBuffalo] = static_cast<int>(25.0 * YEAR_LENGTH);
  arr[Animal::Rabbit] = static_cast<int>(9.0 * YEAR_LENGTH);
  arr[Animal::Antelope] = static_cast<int>(12.0 * YEAR_LENGTH);
  arr[Animal::Deer] = static_cast<int>(15.0 * YEAR_LENGTH);
  arr[Animal::Moose] = static_cast<int>(20.0 * YEAR_LENGTH);
  arr[Animal::Capybara] = static_cast<int>(10.0 * YEAR_LENGTH);
  arr[Animal::Turtle] = static_cast<int>(80.0 * YEAR_LENGTH);
  arr[Animal::Elephant] = static_cast<int>(70.0 * YEAR_LENGTH);
  arr[Animal::Bison] = static_cast<int>(20.0 * YEAR_LENGTH);
  arr[Animal::Wolf] = static_cast<int>(13.0 * YEAR_LENGTH);
  arr[Animal::Bear] = static_cast<int>(25.0 * YEAR_LENGTH);
  arr[Animal::Caribou] = static_cast<int>(15.0 * YEAR_LENGTH);
  arr[Animal::Fish] = static_cast<int>(5.0 * YEAR_LENGTH);

  return arr;
}();

inline LookupTable<Animal, uint16_t> hungerSearchThreshold = [] {
  LookupTable<Animal, uint16_t> arr;
  using enum Animal;
  
  return arr;
}();

  inline constexpr LookupTable<Animal, uint16_t> sightRanges = [] {
    LookupTable<Animal, uint16_t> arr;

    arr[Animal::Pig] = 50;
    arr[Animal::Cow] = 150;
    arr[Animal::Chicken] = 30;
    arr[Animal::Duck] = 80;
    arr[Animal::Sheep] = 200;
    arr[Animal::Goat] = 250;
    arr[Animal::Horse] = 300;
    arr[Animal::Ox] = 150;
    arr[Animal::Donkey] = 200;
    arr[Animal::Camel] = 500;
    arr[Animal::WaterBuffalo] = 100;
    arr[Animal::Rabbit] = 100;
    arr[Animal::Antelope] = 600;
    arr[Animal::Deer] = 500;
    arr[Animal::Moose] = 300;
    arr[Animal::Capybara] = 80;
    arr[Animal::Turtle] = 30;
    arr[Animal::Elephant] = 200;
    arr[Animal::Bison] = 300;
    arr[Animal::Wolf] = 1000;
    arr[Animal::Bear] = 400;
    arr[Animal::Caribou] = 600;
    arr[Animal::Fish] = 20;

    return arr;
}();

inline constexpr LookupTable<Animal, Speed> minSpeed = [] {
  LookupTable<Animal, Speed> arr;

    arr[Animal::Pig] = 1.5f;
    arr[Animal::Cow] = 1.0f;
    arr[Animal::Chicken] = 0.8f;
    arr[Animal::Duck] = 0.8f;
    arr[Animal::Sheep] = 1.0f;
    arr[Animal::Goat] = 1.0f;
    arr[Animal::Horse] = 1.6f;
    arr[Animal::Ox] = 1.0f;
    arr[Animal::Donkey] = 1.2f;
    arr[Animal::Camel] = 1.3f;
    arr[Animal::WaterBuffalo] = 0.9f;
    arr[Animal::Rabbit] = 1.0f;
    arr[Animal::Antelope] = 2.0f;
    arr[Animal::Deer] = 1.8f;
    arr[Animal::Moose] = 1.2f;
    arr[Animal::Capybara] = 0.8f;
    arr[Animal::Turtle] = 0.05f;
    arr[Animal::Elephant] = 1.5f;
    arr[Animal::Bison] = 1.5f;
    arr[Animal::Wolf] = 1.8f;
    arr[Animal::Bear] = 1.3f;
    arr[Animal::Caribou] = 1.8f;
    arr[Animal::Fish] = 0.5f;

    return arr;
}();


inline constexpr LookupTable<Animal, Speed> maxSpeed = [] {
  LookupTable<Animal, Speed> arr;

  arr[Animal::Pig] = 6.0f;
  arr[Animal::Cow] = 7.5f;
  arr[Animal::Chicken] = 4.0f;
  arr[Animal::Duck] = 10.0f;
  arr[Animal::Sheep] = 14.0f;
  arr[Animal::Goat] = 12.0f;
  arr[Animal::Horse] = 22.0f;
  arr[Animal::Ox] = 5.5f;
  arr[Animal::Donkey] = 8.3f;
  arr[Animal::Camel] = 14.0f;
  arr[Animal::WaterBuffalo] = 5.0f;
  arr[Animal::Rabbit] = 17.0f;
  arr[Animal::Antelope] = 27.0f;
  arr[Animal::Deer] = 22.0f;
  arr[Animal::Moose] = 15.0f;
  arr[Animal::Capybara] = 8.3f;
  arr[Animal::Turtle] = 0.3f;
  arr[Animal::Elephant] = 6.8f;
  arr[Animal::Bison] = 18.0f;
  arr[Animal::Wolf] = 17.0f;
  arr[Animal::Bear] = 13.4f;
  arr[Animal::Caribou] = 20.0f;
  arr[Animal::Fish] = 8.0f;

  return arr;
}();

inline constexpr LookupTable<Animal, Health> maxHealths = [] {
  LookupTable<Animal,Health> lt{};
  using enum Animal;
  
  return lt;
}();

inline constexpr LookupTable<Animal, Hunger> maxHungers = [] {
  LookupTable<Animal,Hunger> lt{};
  using enum Animal;
  
  return lt;
}();

inline constexpr LookupTable<Animal,Time> maxAges = [] {
  LookupTable<Animal,Time> lt{};
  using enum Animal;
  
  return lt;
 }();

inline constexpr BitsetTable<Animal> isEggLayer =
[] {
    BitsetTable<Animal> b;
    b.set(Animal::Chicken);
    b.set(Animal::Duck);
    b.set(Animal::Turtle);
    b.set(Animal::Fish);
    return b;
}();



#endif
