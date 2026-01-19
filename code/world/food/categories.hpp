#include <basic/structs.hpp>
#include <plant/enum.hpp>
#include <animal/enum.hpp>


  
enum class Category {
  Leaves,
  Fruit,
  Tuber,
  Birds,
  Fish,
  SmallMammals,
  MediumMammals,
  SmallReptiles,
  LargeReptiles,
  MAX
};

constexpr BitsetTable<Category> meatCategories = [] {
  BitsetTable<Category> s;
  using enum Category;  
  s.set(SmallMammals);
  s.set(MediumMammals);
  s.set(SmallReptiles);
  s.set(LargeReptiles);
  return s;
 };

// TODO height of plant factored
  // TODO  'attraction factor' (some bitter or repulsive plants avoided)
constexpr BitsetTable<Plant> leaves = [] {
  BitsetTable<Plant> s;
  using enum Plant;
  s.set(Fern);
  s.set(PioneerTree);
  s.set(DeciduousTree);
  s.set(EvergreenTree);
  s.set(Kale);
  s.set(Lettuce);
  s.set(Mint);
  s.set(Thyme);
  s.set(Sage);
  s.set(Bush);
  s.set(Rhubarb);
  //flowers
  s.set(Broccoli);
  s.set(Cauliflower);
  return s;
};


constexpr BitsetTable<Plant> fruit = [] {
  BitsetTable<Plant> s;
  using enum Plant;
  s.set(Orange);
  s.set(Apple);
  s.set(Lemon);
  s.set(Pear);
  s.set(Peach);
  s.set(Cherry);
  s.set(Apricot);
  s.set(Plum);
  s.set(Lime);
  s.set(Blueberry);
  s.set(Strawberry);
  s.set(Grape);

  // maybe
  s.set(Cocoa);  
    return s;
};

 constexpr BitsetTable<plant::Type> grains = [] {
      BitsetTable<plant::Type> s;
      s.set(Wheat);
      s.set(Corn);
      s.set(Oat);
      s.set(Rice);
  return s;
 };


 constexpr BitsetTable<plant::Type> underground = [] {
   BitsetTable<plant::Type> s;
   s.set(Potato);
   s.set(Carrot);
   s.set(Yam);
   s.set(Onion);
   s.set(Garlic);
   s.set(Beets);
   s.set(Ginseng);
   return s;
 };

  constexpr BitsetTable<plant::Type> stems = [] {
    BitsetTable<plant::Type> s;
    s.set(Papyrus);
    s.set(Reed);
    s.set(Sugarcane);
    return s;
  };

  constexpr BitsetTable<animal::Type> birds = [] {
    BitsetTable<animal::Type> s;
    s.set(Duck);
    s.set(Chicken);
    return s;
  };

  constexpr BitsetTable<animal::Type> fish = [] {
    BitsetTable<animal::Type> s;
    
    return s;
  };

  constexpr BitsetTable<animal::Type> smallMammals = [] {
    BitsetTable<animal::Type> s;
    s.set(Rabbit);
    return s;
  };

  constexpr BitsetTable<animal::Type> mediumMammals = [] {
    BitsetTable<animal::Type> s;
    s.set(Pig);
    s.set(Sheep);
    s.set(Deer);
    s.set(Capybara);
    s.set(Donkey);
    s.set(Caribou);
    s.set(Goat);
    return s;
  };

  constexpr BitsetTable<animal::Type> largeMammals = [] {
    BitsetTable<animal::Type> s;
    s.set(Cow);
    s.set(Ox);
    s.set(Moose);
    s.set(Horse);
    s.set(Camel);
    s.set(WaterBuffalo);
    s.set(Antelope);
    s.set(Bison);
    return s;
  };

  constexpr BitsetTable<animal::Type> smallReptiles = [] {
    BitsetTable<animal::Type> s;
    s.set(Turtle);   
    return s;
  };

  constexpr BitsetTable<animal::Type> largeReptiles = [] {
    BitsetTable<animal::Type> s;
    
    return s;
  };

  
}
