#ifndef DIETS_HPP
#define DIETS_HPP

#include <cassert>
#include <core/containers.hpp>
#include <data/types/animal.hpp>
#include <data/types/plant.hpp>
#include "enum.hpp"
#include "core/tables.hpp"
#include "animal_diet_categories.hpp"

inline constexpr BitsetTable<Animal> CARNIVORES = []
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

inline const RaggedLookupTable<Animal, Category> DIET_CATEGORIES = []
{
	RaggedLookupTable<Animal, Category> lt{};
	using enum Category;
	lt.set(Animal::NONE, {});
	lt.set(Animal::Pig, {Grasses, Leaves, Fruits, Tubers, SmallMammals, SmallReptiles});
	lt.set(Animal::Cow, {Grasses, Leaves});
	lt.set(Animal::Chicken, {Leaves, Fruits, Reeds});
	lt.set(Animal::Duck, {Leaves, Fruits, Fishes, Reeds});
	lt.set(Animal::Sheep, {Leaves});
	lt.set(Animal::Goat, {Leaves, Fruits, Tubers});
	lt.set(Animal::Horse, {Grasses, Leaves});
	lt.set(Animal::Ox, {Grasses, Leaves});
	lt.set(Animal::Donkey, {Grasses, Leaves});
	lt.set(Animal::Camel, {Grasses, Leaves, Fruits});
	lt.set(Animal::WaterBuffalo, {Grasses, Leaves});
	lt.set(Animal::Rabbit, {Grasses, Leaves, Fruits, Tubers});
	lt.set(Animal::Antelope, {Grasses, Leaves, Fruits});
	lt.set(Animal::Deer, {Grasses, Leaves, Fruits, Tubers});
	lt.set(Animal::Moose, {Grasses, Leaves, Fruits});
	lt.set(Animal::Capybara, {Leaves, Fruits});
	lt.set(Animal::Turtle, {Leaves, Fruits, Fishes});
	lt.set(Animal::Elephant, {Leaves, Fruits, Tubers});
	lt.set(Animal::Bison, {Grasses, Leaves});
	lt.set(Animal::Caribou, {Grasses, Leaves, Tubers, Fruits});
	lt.set(Animal::Wolf, {MediumMammals, SmallMammals, Birds, Fishes, SmallReptiles});
	lt.set(Animal::Bear, {Leaves, Fruits, Fishes, SmallMammals, MediumMammals, Birds, SmallReptiles});

	return lt;
}();

const BitsetTable<Animal> &get_animal_food_table(const Category c)
{
		using enum Category;
		switch (c) {
		case Birds:
		return BIRDS;
	case Fishes:
		return FISHES;
	case SmallMammals:
		return SMALL_MAMMALS;
	case MediumMammals:
		return MEDIUM_MAMMALS;
	case LargeMammals:
		return LARGE_MAMMALS;
	case SmallReptiles:
		return SMALL_REPTILES;
	case LargeReptiles:
		return LARGE_REPTILES;
	default:
#if !SHIPPING_BUILD
				assert(true != true && "Tried to get animal food table from non-animal food category.");
#endif			
	}
}


const BitsetTable<Plant> &get_plant_food_table(const Category c)
{
		using enum Category;
		switch (c) {
		case Leaves:
		return LEAVES;
	case Fruits:
		return FRUITS;
	case Grains:
		return GRAINS;
	case Undergrounds:
		return UNDERGROUNDS;
	case Stems:
		return STEMS;
	default:
#if !SHIPPING_BUILD
				assert(true != true && "Tried to get plant food table from non-plant food category.");
#endif			
	}
}


BitsetTable<Plant> get_herbivore_diet(Animal a)
{
	std::span<const Category> cats = DIET_CATEGORIES.get(a);
	BitsetTable<Plant> b;
	for (const Category x : cats)
		if (!MEAT_CATEGORIES[x])
			b |= get_plant_food_table(x);
	return b;
};

BitsetTable<Animal> get_carnivore_diet(Animal a)
{
	std::span<const Category> cats = DIET_CATEGORIES.get(a);
	BitsetTable<Animal> b;
	for (auto x : cats)
		if (MEAT_CATEGORIES[x])
			b |= get_animal_food_table(x);
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
