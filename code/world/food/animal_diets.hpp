#ifndef DIETS_HPP
#define DIETS_HPP

#include <core/containers.hpp>
#include <world/animal/enum.hpp>
#include <world/plant/enum.hpp>
#include "enum.hpp"
#include "core/tables.hpp"

inline constexpr BitsetTable<Animal> carnivores = []
{
	BitsetTable<Animal> s;
	using enum Animal;
	auto add = [&](Animal e) { s.bitset.set(static_cast<uint16_t>(e)); };
	using enum Animal;
	add(Pig);
    add(Wolf);
    add(Bear);
	return s;
}();

inline const RaggedLookupTable<Animal, Category> dietCategories = []
{
	RaggedLookupTable<Animal, Category> lt{};
	using enum Category;
	lt.set(Animal::NONE, {});
	lt.set(Animal::Pig, {Grass, Leaves, Fruit, Tuber, SmallMammals, SmallReptiles});
	lt.set(Animal::Cow, {Grass, Leaves});
	lt.set(Animal::Chicken, {Leaves, Fruit, Reeds});
	lt.set(Animal::Duck, {Leaves, Fruit, Fish, Reeds});
	lt.set(Animal::Sheep, {Leaves});
	lt.set(Animal::Goat, {Leaves, Fruit, Tuber});
	lt.set(Animal::Horse, {Grass, Leaves});
	lt.set(Animal::Ox, {Grass, Leaves});
	lt.set(Animal::Donkey, {Grass, Leaves});
	lt.set(Animal::Camel, {Grass, Leaves, Fruit});
	lt.set(Animal::WaterBuffalo, {Grass, Leaves});
	lt.set(Animal::Rabbit, {Grass, Leaves, Fruit, Tuber});
	lt.set(Animal::Antelope, {Grass, Leaves, Fruit});
	lt.set(Animal::Deer, {Grass, Leaves, Fruit, Tuber});
	lt.set(Animal::Moose, {Grass, Leaves, Fruit});
	lt.set(Animal::Capybara, {Leaves, Fruit});
	lt.set(Animal::Turtle, {Leaves, Fruit, Fish});
	lt.set(Animal::Elephant, {Leaves, Fruit, Tuber});
	lt.set(Animal::Bison, {Grass, Leaves});
	lt.set(Animal::Caribou, {Grass, Leaves, Tuber, Fruit});
	lt.set(Animal::Wolf, {MediumMammals, SmallMammals, Birds, Fish, SmallReptiles});
	lt.set(Animal::Bear, {Leaves, Fruit, Fish, SmallMammals, MediumMammals, Birds, SmallReptiles});

	return lt;
}();

template <typename E>
BitsetTable<E> &getFoodTable(const Category c)
{
	using enum Category;
	switch (c)
	{
	case Leaves:
		return leaves;
	case Fruit:
		return fruits;
	case Grain:
		return grains;
	case Underground:
		return undergrounds;
	case Stem:
		return stems;
	case Birds:
		return birds;
	case Fish:
		return fish;
	case SmallMammals:
			return smallMammals;
	case MediumMammals:
			return mediumMammals;
	case LargeMammals:
		return largeMammals;
	case SmallReptiles:
		return smallReptiles;
	case LargeReptiles:
		return largeReptiles;
	}
};


BitsetTable<Plant> getHerbivoreDiet(Animal a)
{
	std::span<const Category> cats = dietCategories.get(a);
	BitsetTable<Plant> b;
	for (const Category x : cats)
		if (!meatCategories[x])
			b |= getFoodTable<Plant>(x);
	return b;
};

BitsetTable<Animal> getCarnivoreDiet(Animal a)
{
	std::array<Category, 5> &cats = dietCategories[a];
	BitsetTable<Animal> b;
	for (auto x : cats)
		if (meatCategories[x])
			b |= getFoodTable<Animal>(x);
	return b;
};

inline const LookupTable<Animal, BitsetTable<Plant>> herbivoreDiets = []
{
	LookupTable<Animal, BitsetTable<Plant>> lt{};
	using enum Animal;
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

inline const LookupTable<Animal, BitsetTable<Animal>> carnivoreDiets = []
{
	LookupTable<Animal, BitsetTable<Animal>> lt{};
    using enum Animal;
	lt[Pig] = getCarnivoreDiet(Pig);
	lt[Wolf] = getCarnivoreDiet(Wolf);
	lt[Bear] = getCarnivoreDiet(Bear);

	return lt;
}();

#endif
