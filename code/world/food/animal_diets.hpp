#ifndef DIETS_HPP
#define DIETS_HPP

#include "categories.hpp"
#include <core/containers.hpp>
#include <world/animal/enum.hpp>
#include <world/plant/enum.hpp>

inline constexpr BitsetTable<Animal> carnivores = []
{
	BitsetTable<Animal> s;
	using enum Animal;
	s[Pig] = true;
	s[Wolf] = true;
	s[Bear] = true;
	return s;
};

inline constexpr LookupTable2D<Animal, Category> dietCategories = []
{
	LookupTable2D<Animal, Category> lt{};
	using enum Animal;
	lt[NONE] = {};
	lt[Pig] = {Grass, Leaves, Fruit, Tuber, SmallMammals, SmallReptiles};
	lt[Cow] = {Grass, Leaves};
	lt[Chicken] = {Leaves, Fruit, Reeds};
	lt[Duck] = {Leaves, Fruit, Fish, Reeds};
	lt[Sheep] = {Leaves};
	lt[Goat] = {Leaves, Fruit, Tuber};
	lt[Horse] = {Grass, Leaves};
	lt[Ox] = {Grass, Leaves};
	lt[Donkey] = {Grass, Leaves};
	lt[Camel] = {Grass, Leaves, Fruit};
	lt[WaterBuffalo] = {Grass, Leaves};
	lt[Rabbit] = {Grass, Leaves, Fruit, Tuber};
	lt[Antelope] = {Grass, Leaves, Fruit};
	lt[Deer] = {Grass, Leaves, Fruit, Tuber};
	lt[Moose] = {Grass, Leaves, Fruit};
	lt[Capybara] = {Leaves, Fruit};
	lt[Turtle] = {Leaves, Fruit, Fish};
	lt[Elephant] = {Leaves, Fruit, Tuber};
	lt[Bison] = {Grass, Leaves};
	lt[Caribou] = {Grass, Leaves, Tuber, Fruit};

	lt[Wolf] = {MediumMammals, SmallMammals, Birds, Fish, SmallReptiles};
	lt[Bear] = {Leaves, Fruit, Fish, SmallMammals, MediumMammals, Birds, SmallReptiles};

	lt[MAX] = {};

	return lt;
}();

BitsetTable &getFoodTable(Category c)
{
	switch (c)
	{
	case Leaves:
		return leaves;
	case Fruit:
		return fruit;
	case Grain:
		return grain;
	case Underground:
		return underground;
	case Stem:
		return stem;
	case Birds:
		return birds;
	case Fish:
		return fish;
	case SmallMammals:
		return smallMammals;
	case LargeMammals:
		return largeMammals;
	case SmallReptiles:
		return smallReptiles;
	case LargeReptiles:
		return largeReptiles;
	}
};

BitSetTable getHerbivoreDiet(Animal a)
{
	std::array<Category, 5> &cats = dietCategories[a];
	BitSetTable b;
	for (auto x : cats)
		if !(meatCategories[x])
			b |= getFoodTable(x);
	return b;
};

BitSetTable getCarnivoreDiet(Animal a)
{
	std::array<Category, 5> &cats = dietCategories[a];
	BitSetTable b;
	for (auto x : cats)
		if (meatCategories[x])
			b |= getFoodTable(x);
	return b;
};

inline constexpr LookupTable<BitsetTable<Animal>> herbivoreDiets = []
{
	LookupTable<BitsetTable<Animal>> lt{};
	lt[Pig] = getHerbivoreDiet(Pig);
	lt[Cow] = getHerbivoreDiet(Cow);
	lt[Chicken] = getHerbivoreDiet(Chicken);
	lt[Duck] = getHerbivoreDiet(Duck);
	lt[Sheep] = getHerbivoreDiet(Sheep);
	lt[Goat] = getHerbivoreDiet(Goat);
	lt[Horse] = getHerbivoreDiet(Horse);
	lt[Ox] = getHerbivoreDiet(Ox);
	lt[Donkey] = getHerbivoreDiet(Donkey);
	lt[Camel] = getHerbivoreDiet(Camel);
	lt[WaterBuffalo] = getHerbivoreDiet(WaterBuffalo);
	lt[Rabbit] = getHerbivoreDiet(Rabbit);
	lt[Antelope] = getHerbivoreDiet(Antelope);
	lt[Deer] = getHerbivoreDiet(Deer);
	lt[Moose] = getHerbivoreDiet(Moose);
	lt[Capybara] = getHerbivoreDiet(Capybara);
	lt[Turtle] = getHerbivoreDiet(Turtle);
	lt[Elephant] = getHerbivoreDiet(Elephant);
	lt[Bison] = getHerbivoreDiet(Bison);
	lt[Caribou] = getHerbivoreDiet(Caribou);
	return lt;
}();

inline constexpr LookupTable<BitsetTable<Animal>> carnivoreDiets = []
{
	LookupTable<BitsetTable<Animal>> lt{};

	lt[Pig] = getCarnivoreDiet(Pig);
	lt[Wolf] = getCarnivoreDiet(Wolf);
	lt[Bear] = getCarnivoreDiet(Bear);

	return lt;
}();

#endif
