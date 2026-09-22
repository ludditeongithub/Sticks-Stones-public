#include <data/types/animal.hpp>
#include <data/types/plant.hpp>
#include <core/tables.hpp>
#include "enum.hpp"

inline constexpr const BitsetTable<Category> MEAT_CATEGORIES = []
{
	BitsetTable<Category> s;
	auto add = [&](Category e) {s.bitset.set(static_cast<uint16_t>(e)); };
	using enum Category;
	add(SmallMammals);
	add(MediumMammals);
	add(SmallReptiles);
	add(LargeReptiles);
	return s;
}();

// TODO height of plant factored
// TODO  'attraction factor' (some bitter or repulsive plants avoided)
inline constexpr const BitsetTable<Plant> LEAVES = []
{
	BitsetTable<Plant> s;
	auto add = [&](Plant e) {s.bitset.set(static_cast<uint16_t>(e)); };
	using enum Plant;
	add(Fern);
	add(PioneerTree);
	add(DeciduousTree);
	add(EvergreenTree);
	add(Kale);
	add(Lettuce);
	add(Mint);
	add(Thyme);
	add(Sage);
	add(Bush);
	add(Rhubarb);
	// flowers
	add(Broccoli);
	return s;
}();

inline constexpr const BitsetTable<Plant> FRUITS = []
{
	BitsetTable<Plant> s;
	auto add = [&](Plant e) {s.bitset.set(static_cast<uint16_t>(e)); };	
	using enum Plant;
	add(Orange);
	add(Apple);
	add(Lemon);
	add(Pear);
	add(Peach);
	add(Cherry);
	add(Apricot);
	add(Plum);
	add(Lime);
	add(Blueberry);
	add(Strawberry);
	// maybe
	add(Cocoa);
	return s;
}();

inline constexpr const BitsetTable<Plant> GRAINS = []
{
	BitsetTable<Plant> s;
	using enum Plant;
	auto add = [&](Plant e) {s.bitset.set(static_cast<uint16_t>(e)); };
	add(Wheat);
	add(Corn);
	add(Oat);
	add(Rice);
	return s;
}();

inline constexpr const BitsetTable<Plant> UNDERGROUNDS = []
{
	BitsetTable<Plant> s;
	using enum Plant;
	auto add = [&](Plant e) {s.bitset.set(static_cast<uint16_t>(e)); };
	add(Potato);
	add(Carrot);
	add(Onion);
	add(Garlic);
	add(Beets);
	add(Ginseng);
	return s;
}();

inline constexpr const BitsetTable<Plant> STEMS = []
{
	BitsetTable<Plant> s;
	using enum Plant;
	auto add = [&](Plant e) {s.bitset.set(static_cast<uint16_t>(e)); };	
	add(Papyrus);
	add(Reed);
	return s;
}();

inline constexpr const BitsetTable<Animal> BIRDS = []
{
		BitsetTable<Animal> s;
		auto add = [&](Animal e) { s.bitset.set(static_cast<uint16_t>(e)); };
		using enum Animal;
	add(Duck);
	add(Chicken);
	return s;
}();

inline constexpr const BitsetTable<Animal> FISHES = []
{
	BitsetTable<Animal> s;

	return s;
}();

inline constexpr const BitsetTable<Animal> SMALL_MAMMALS = []
{
		BitsetTable<Animal> s;
	auto add = [&](Animal e) { s.bitset.set(static_cast<uint16_t>(e)); };
		using enum Animal;
	add(Rabbit);
	return s;
}();

inline constexpr const BitsetTable<Animal> MEDIUM_MAMMALS = []
{
		BitsetTable<Animal> s;
			auto add = [&](Animal e) { s.bitset.set(static_cast<uint16_t>(e)); };
		using enum Animal;
	add(Pig);
	add(Sheep);
	add(Deer);
	add(Capybara);
	add(Donkey);
	add(Caribou);
	add(Goat);
	return s;
}();

inline constexpr const BitsetTable<Animal> LARGE_MAMMALS = []
{
		BitsetTable<Animal> s;
			auto add = [&](Animal e) { s.bitset.set(static_cast<uint16_t>(e)); };
		using enum Animal;
	add(Cow);
	add(Ox);
	add(Moose);
	add(Horse);
	add(Camel);
	add(WaterBuffalo);
	add(Antelope);
	add(Bison);
	return s;
}();

inline constexpr const BitsetTable<Animal> SMALL_REPTILES = []
{
		BitsetTable<Animal> s;
			auto add = [&](Animal e) { s.bitset.set(static_cast<uint16_t>(e)); };
		using enum Animal;
	add(Turtle);
	return s;
}();

inline constexpr const BitsetTable<Animal> LARGE_REPTILES = []
{
	BitsetTable<Animal> s;
auto add = [&](Animal e) { s.bitset.set(static_cast<uint16_t>(e)); };
		using enum Animal;
	return s;
}();

