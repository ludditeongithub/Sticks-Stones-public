#pragma once
#include <data/types/item.hpp>
#include <data/types/buildable.hpp>

using Commodity = ConcatEnum<Item, Buildable, knowledge::Category, order::Category, Ritual, PlantCategory, Animal>;

