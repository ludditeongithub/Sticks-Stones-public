#pragma once
#include <cstdint>
#include <data/types/item.hpp>
#include <data/types/buildable.hpp>
#include <data/types/progression.hpp>
#include <data/types/plant.hpp>
#include <data/types/animal.hpp>
#include <data/types/container.hpp>
#include <data/types/unit.hpp>
#include <data/const/unit_data.hpp>
#include <core/combo_enum.hpp>

using Time = uint32_t;
using Frame = uint16_t;

// general
using EntityID = std::size_t;
using Variant = uint8_t;
//consider putting Material into commodity, which will determine possible material variants for all items if applicable. alternatively, pairs which include item and variant int8_t cast from material
// important: must be initialized in enum order!
using Commodity = ConcatEnum<Item, Buildable, knowledge::Category, order::Category, Ritual, PlantCategory, Animal>;  

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

using Roles = std::array<Role, MAX_ROLES>;
using RoleMana = uint8_t;
using Places = std::array<Place, 3>;

