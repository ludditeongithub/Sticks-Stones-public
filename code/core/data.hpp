#pragma once
#include <cstdint>

using Time = uint32_t;
using Frame = uint16_t;

// general
using EntityID = std::size_t;
using Variant = uint8_t;

// geography
using Hum = uint16_t;
using Temp = uint16_t;
using Alt = uint8_t;
using Liquid = uint16_t;
using WeatherValue = uint8_t;

// unit stats
using Health = float; //also for Buildable
using Speed = float;
using Hunger = uint16_t;
using Sex = bool;
using Priority = uint8_t;
using RoleMana = uint8_t;

// unit skills
constexpr uint8_t STAT_MAX = 100;
using Strength = uint8_t;
using Athleticism = uint8_t;
using Dexterity = uint8_t;
using Intellect = uint8_t;
using Memory = uint8_t;
using Perception = uint8_t;
using Creativity = uint8_t;
using Charisma = uint8_t;
using Determination = uint8_t;

using CloudKey = uint8_t;
using PrecipitationKey = uint8_t;
using Precipitation = float;

enum class TargetType : uint8_t
{
	NONE,
	Animal,
	Plant,
	Item,
	Unit,
	Tile,
	Buildable
};

struct Target
{
	TargetType type;
	std::size_t index;
};

// Food
enum class FoodEnjoyment
{
	Trash,
	Horrid,
	Poor,
	Mediocre,
	Good,
	Great,
    Legendary
};
