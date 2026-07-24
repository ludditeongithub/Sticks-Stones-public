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

inline const RaggedLookupTable<Animal, Category> diet_categories = []
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
BitsetTable<E> &get_food_table(const Category c)
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
			return small_mammals;
	case MediumMammals:
			return medium_mammals;
	case LargeMammals:
		return large_mammals;
	case SmallReptiles:
		return small_reptiles;
	case LargeReptiles:
		return large_reptiles;
	}
};


BitsetTable<Plant> get_herbivore_diet(Animal a)
{
	std::span<const Category> cats = diet_categories.get(a);
	BitsetTable<Plant> b;
	for (const Category x : cats)
		if (!meat_categories[x])
			b |= get_food_table<Plant>(x);
	return b;
};

BitsetTable<Animal> get_carnivore_diet(Animal a)
{
	std::array<Category, 5> &cats = diet_categories[a];
	BitsetTable<Animal> b;
	for (auto x : cats)
		if (meat_categories[x])
			b |= get_food_table<Animal>(x);
	return b;
};

inline const LookupTable<Animal, BitsetTable<Plant>> herbivore_diets = []
{
	LookupTable<Animal, BitsetTable<Plant>> lt{};
	using enum Animal;
	lt[Pig] = get_herbivore_diet(Pig);
	lt[Cow] = get_herbivore_diet(Cow);
	lt[Chicken] = get_herbivore_diet(Chicken);
	lt[Duck] = get_herbivore_diet(Duck);
	lt[Sheep] = get_herbivore_diet(Sheep);
	lt[Goat] = get_herbivore_diet(Goat);
	lt[Horse] = get_herbivore_diet(Horse);
	lt[Ox] = get_herbivore_diet(Ox);
	lt[Donkey] = get_herbivore_diet(Donkey);
	lt[Camel] = get_herbivore_diet(Camel);
	lt[WaterBuffalo] = get_herbivore_diet(WaterBuffalo);
	lt[Rabbit] = get_herbivore_diet(Rabbit);
	lt[Antelope] = get_herbivore_diet(Antelope);
	lt[Deer] = get_herbivore_diet(Deer);
	lt[Moose] = get_herbivore_diet(Moose);
	lt[Capybara] = get_herbivore_diet(Capybara);
	lt[Turtle] = get_herbivore_diet(Turtle);
	lt[Elephant] = get_herbivore_diet(Elephant);
	lt[Bison] = get_herbivore_diet(Bison);
	lt[Caribou] = get_herbivore_diet(Caribou);
	return lt;
}();

inline const LookupTable<Animal, BitsetTable<Animal>> carnivore_diets = []
{
	LookupTable<Animal, BitsetTable<Animal>> lt{};
    using enum Animal;
	lt[Pig] = get_carnivore_diet(Pig);
	lt[Wolf] = get_carnivore_diet(Wolf);
	lt[Bear] = get_carnivore_diet(Bear);

	return lt;
}();

#endif
