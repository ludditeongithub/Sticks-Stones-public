#pragma once
#include <cstdint>
#include <unordered_map>
#include <array>
#include <vector>
#include <core/data.hpp>
#include <world/world.hpp>
#include <world/item/enum.hpp>

constexpr uint16_t UNIT_CAP = 1000;
using OverflowHashMap = std::unordered_map<uint32_t, std::vector<HoldableSlot>>;
using OverflowContainerMap = std::unordered_map<uint16_t, std::vector<Container>>;

OverflowHashMap g_overflow_hash_map;
OverflowContainerMap g_overflow_container_map;

// the total volume of each bulk category hands can maximally carry.
// where 0.1 is 100mL
// NOTE: idea: consider doing left and right

// mas weights pawns can carry

constexpr uint16_t CONTAINER_UNDERFLOW_LIMIT = 3;
constexpr uint16_t STARTING_SKILL_MAX = 15;
constexpr uint16_t STAT_MAX = 

// Fine means that only fine objects can be carried, mid means that loose, soft, or solid objects
// can be carried, single means that only single objects can be carried

constexpr Frame BASE_WALKING_FRAMES = 8;
constexpr Frame BASE_RUNNING_FRAMES = 8;

float generate_skin_warmth(float parent1, float parent2)
{
	float crossed_value = std::lerp(parent1, parent2, 0.5);
	return std::lerp(crossed_value, random_chance->next(), 0.08);
}

float generate_skin_warmth(World &world, Coord coord)
{
  uint16_t chunk = get_chunk_index_from_tile(coord);
	uint16_t longitude = world.get_chunk_time_zone(chunk);
	return std::lerp(longitude, random_chance->next(), 0.3);
}

float generate_melanin(World& world, Coord coord) {
    uint16_t chunk = get_chunk_index_from_tile(coord);
	uint16_t latitude = world.get_chunk_time_zone(chunk);
	return std::lerp(latitude, random_chance->next(), 0.3);
}

float generate_melanin(float parent1, float parent2) {
        float crossed_value = std::lerp(parent1, parent2, 0.5);
	return std::lerp(crossed_value, random_chance->next(), 0.08);
}

struct Inventory
{
	// TODO
	//  std::variant<ItemSlot, VariantItemSlot, ToolSlot> left_hand;
	//  std::variant<ItemSlot, VariantItemSlot, ToolSlot> right_hand;
	std::array<Container, CONTAINER_UNDERFLOW_LIMIT> containers; // first container is HANDS
	BulkStatus bulk_status = BulkStatus::NONE;		     // for hands
	float weight;
	Inventory()
	{
		containers[0].type = ContainerType::Hands;
		weight = 0;
	}

	bool attempt_hold(Item item) {}
};

struct Skills
{
	Strength strength;
	Athleticism athleticism;
	Dexterity dexterity;
	Intellect intellect;
	Memory memory;
	Perception perception;
	Creativity creativity;
	Charisma charisma;
	Determination determination;

	uint8_t get_random_starting_skill()
	{
		return static_cast<uint8_t>(STARTING_SKILL_MAX * random_chance->next());
	}

	Skills()
	{
		strength = get_random_starting_skill();
		athleticism = get_random_starting_skill();
		dexterity = get_random_starting_skill();
		intellect = get_random_starting_skill();
		perception = get_random_starting_skill();
		creativity = get_random_starting_skill();
		charisma = get_random_starting_skill();
		determination = get_random_starting_skill();
	}
};

constexpr uint8_t MAX_ROLES = 5;
using Roles = std::array<Role, MAX_ROLES>;
using RoleMana = uint8_t;

using Sex = bool;

// places that units own or participate in.
struct Place
{
	Coord pos;
	PlaceType type;
};

using Places = std::array<Place, 3>;
