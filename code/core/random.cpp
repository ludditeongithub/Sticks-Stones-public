#include "random.hpp"

RandomEnumMachine<Direction> random_direction =
		RandomEnumMachine<Direction>(Direction::North, Direction::West);

RandomChanceMachine *random_chance = new RandomChanceMachine();

RandomBoolMachine *random_bool = new RandomBoolMachine();
