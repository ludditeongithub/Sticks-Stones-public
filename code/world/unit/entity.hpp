#pragma once
#include "enum.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/hash.hpp>
#include <core/math.hpp>
#include <core/random.hpp>

#include <extern/cereal/archives/binary.hpp>
#include <cstdint>
#include <stack>
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

// TODO: possibly pack these
using Strength = uint8_t;
using Athleticism = uint8_t;
using Dexterity = uint8_t;
using Intellect = uint8_t;
using Memory = uint8_t;
using Perception = uint8_t;
using Creativity = uint8_t;
using Charisma = uint8_t;
using Determination = uint8_t;

constexpr uint8_t SKILL_MAX = 50;
constexpr uint8_t STARTING_SKILL_MAX = 25;

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

constexpr RoleMana STARTING_ROLE_MANA = 10;
constexpr Health MAX_HEALTH = 100;
constexpr Health INFANT_STARTING_HEALTH_MAX = 50;
constexpr Health INFANT_STARTING_HEALTH_MIN = 38;
constexpr Hunger INFANT_HUNGER_MAX = 850;

// TODO: differentiate between enemy and friendly databases. make this database several connected
// chunks, so that they can be passed at once to render or other
struct UnitDatabase
{
	constexpr static uint16_t ENTITY_SIZE =
	    sizeof(Coord) + sizeof(Direction) + sizeof(Health) + sizeof(Hunger) + sizeof(Time) +
	    sizeof(Action) + sizeof(uint16_t) + sizeof(TargetType) + sizeof(Frame) +
	    sizeof(Inventory) + sizeof(Roles) + sizeof(RoleMana) + sizeof(Skills) + sizeof(Places);

	uint16_t cap;
	uint16_t size;
	std::stack<uint16_t> freeSlots;
	std::vector<bool> alive;

	// processing done with animals
	Array<Coord> coords;
	Array<FrameData> frameDatas;
	Array<Health> healths;
	Array<Hunger> hungers;
	Array<Time> ages;
	Array<Action> actions;
	Array<Target> targets;
	Array<Frame> frames;
	// processing unique to units
	Array<Inventory> inventories;

	// overflows are all seperate, so that
	OverflowHashMap overflows; // index is hashed
	OverflowContainerMap overflowContainers;
 
	std::vector<Sex> sexs;
	Array<Roles> roles;
	Array<RoleMana> roleManas;
	Array<Skills> skills;
	Array<Places> places;

  UnitDatabase(uint16_t s, Arena* arena)
	{
		size = 0;
		cap = s;
		alive = std::vector<bool>(s);
		coords = arena_make_array<Coord>(arena, s);
		frameDatas = arena_make_array<FrameData>(arena, s);
		healths = arena_make_array<Health>(arena, s);
		hungers = arena_make_array<Hunger>(arena, s);
		ages = arena_make_array<Time>(arena, s);
		actions = arena_make_array<Action>(arena, s);
		targets = arena_make_array<Target>(arena, s);
		frames = arena_make_array<Frame>(arena, s);
		inventories = arena_make_array<Inventory>(arena, s);
		sexs = std::vector<Sex>(s);
		roles = arena_make_array<Roles>(arena, s);
		roleManas = arena_make_array<RoleMana>(arena, s);
		skills = arena_make_array<Skills>(arena, s);
		places = arena_make_array<Places>(arena, s);
	}

        template <class Archive>
        UnitDatabase(Arena* arena, Archive& archive)
	{
		archive(cereal::binary_data(arena));
	}

  template <class Archive> void load(Arena* arena, Archive& archive) {
    archive(cereal::binary_data(arena)));
  }

        

	//TODO: make similar birth and kills for other databases (size conscious), make impDatabases if over size, or other management strategy.
	bool birthUnit(Coord c)
	{
		if (size + 1 > cap)
			return false;
		size++;
		if (freeSlots.empty())
		{
			alive.emplace_back(true);
			coords.push(c);
			healths.push(random_chance->next() *
				     (INFANT_STARTING_HEALTH_MAX - INFANT_STARTING_HEALTH_MIN));
			hungers.push(INFANT_HUNGER_MAX);
			ages.push(0);
			actions.push(Action::NONE);
			targets.push({TargetType::NONE, std::numeric_limits<uint16_t>::max()});
			frameDatas.push({ActState::NewPath, random_direction->next(), 0});
			inventories.push(Inventory());
			sexs.emplace_back(random_bool->next());
			roles.push({});
			roleManas.push(STARTING_ROLE_MANA);
			skills.push(Skills());
			places.push({});
		}
		else
		{
			uint16_t i = freeSlots.top();
			freeSlots.pop();

			coords[i] = c;
			frameDatas[i] = {ActState::NewPath, random_direction->next(), 0};
			healths[i] = random_chance->next() *
				     (INFANT_STARTING_HEALTH_MAX - INFANT_STARTING_HEALTH_MIN);
			hungers[i] = INFANT_HUNGER_MAX;
			ages[i] = 0;
			actions[i] = Action::NONE;
			targets[i] = {TargetType::NONE, std::numeric_limits<uint16_t>::max()};
			inventories[i] = Inventory();
			sexs[i] = random_bool->next();
			roles[i] = {};
			roleManas[i] = STARTING_ROLE_MANA;
			skills[i] = Skills();
			places[i] = {};
		}
	}

	void killUnit(uint16_t i)
	{
		if (alive[i] == false)
		{
			std::cerr << "Tried to kill already dead unit." << std::endl;
		}
		else
		{
			alive[i] = false;
			freeSlots.push(i);
		}
	}
};
