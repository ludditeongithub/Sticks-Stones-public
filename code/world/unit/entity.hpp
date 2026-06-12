#pragma once
#include "enum.hpp"
#include <macros/database.hpp>
#include <macros/serialization.hpp>
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/hash.hpp>
#include <core/math.hpp>
#include <core/random.hpp>
#include <macros/database.hpp>
#include <extern/cereal/archives/binary.hpp>
#include <cstdint>
#include <stack>
#include <vector>
#include <unordered_map>
#include <world/defaults.hpp>
#include <world/item/container.hpp>
#include <world/item/entity.hpp>
#include <world/item/enum.hpp>
#include <world/item/stats.hpp>
#include <world/tile/data.hpp>
#include <world/world.hpp>

using OverflowHashMap = std::unordered_map<uint32_t, std::vector<HoldableSlot>>;

using OverflowContainerMap = std::unordered_map<uint16_t, std::vector<Container>>;

constexpr uint16_t UNIT_CAP = 1000;

// the total volume of each bulk category hands can maximally carry.
// where 0.1 is 100mL
// NOTE: idea: consider doing left and right

// mas weights pawns can carry

constexpr uint16_t CONTAINER_UNDERFLOW_LIMIT = 3;

// Fine means that only fine objects can be carried, mid means that loose, soft, or solid objects
// can be carried, single means that only single objects can be carried

struct Inventory
{
	// TODO
	//  std::variant<ItemSlot, VariantItemSlot, ToolSlot> leftHand;
	//  std::variant<ItemSlot, VariantItemSlot, ToolSlot> rightHand;
	std::array<Container, CONTAINER_UNDERFLOW_LIMIT> containers; // first container is HANDS
	BulkStatus bulkStatus = BulkStatus::NONE;		     // for hands
	float weight;
	Inventory()
	{
		containers[0].type = ContainerType::Hands;
		weight = 0;
	}

	bool attemptHold(Item item) {}
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

	uint8_t getRandomStartingSkill()
	{
		return static_cast<uint8_t>(STARTING_SKILL_MAX * random_chance->next());
	}

	Skills()
	{
		strength = getRandomStartingSkill();
		athleticism = getRandomStartingSkill();
		dexterity = getRandomStartingSkill();
		intellect = getRandomStartingSkill();
		perception = getRandomStartingSkill();
		creativity = getRandomStartingSkill();
		charisma = getRandomStartingSkill();
		determination = getRandomStartingSkill();
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

// TODO: differentiate between enemy and friendly databases. make this database several connected
// chunks, so that they can be passed at once to render or other
struct UnitDatabase
{		
	constexpr static uint16_t ENTITY_SIZE =
	    sizeof(Coord) + sizeof(Direction) + sizeof(Health) + sizeof(Hunger) + sizeof(Time) +
	    sizeof(Action) + sizeof(uint16_t) + sizeof(TargetType) + sizeof(Frame) +
	    sizeof(Inventory) + sizeof(Roles) + sizeof(RoleMana) + sizeof(Skills) + sizeof(Places);

#define UNIT_RUNTIME_ARRAYS(X) \
    X(Coord, coords, coord) \
	X(FrameData, frameDatas, defaults::FRAME_DATA) \
	X(Health, healths, defaults::UNIT_HEALTH) \
	X(Hunger, hungers, defaults::INFANT_HUNGER_MAX) \
    X(Time, ages, 0) \
    X(Action, actions, Action::NONE) \
	X(Target, targets, defaults::TARGET) \
	X(Frame, frames, 0) \
    X(Inventory, inventories, Inventory{}) \
    X(Sex, sexes, random_bool->next()) \
    X(Roles, roles, Roles{}) \
	X(RoleMana, roleManas, defaults::STARTING_ROLE_MANA) \
    X(Skills, skills, Skills{}) \
    X(Places, places, Places{})
				//overflows are all separate. index is hased for OverflowHashMap
#define UNIT_INDEPENDENT_MEMBERS(X)                                                                \
	X(OverflowHashMap, overflows)                                                              \
		X(OverflowContainerMap, overflowContainer)

#define UNIT_STD_CONTAINERS(X)

		// DEFAULT_DATABASE_DECLARATION(UNIT);

		// UnitDatabase(Arena *arena, size_t capacity) { UNIT_RUNTIME_ARRAYS(INIT_ARRAY); }

		// DECLARE_STRUCT_SERIALIZATION(UNIT);

		DEFAULT_DATABASE_CREATION(UNIT);
};
