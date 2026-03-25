#pragma once
#include "data.hpp"
#include <array>
#include <limits>
#include <random>
#include <type_traits>

static std::random_device rd;
static std::mt19937 gen(rd());


template <typename T> struct RandomMachine
{
	static constexpr uint16_t PREGENERATED_RANDOM_SIZE = 15000;
	std::array<T, PREGENERATED_RANDOM_SIZE> randoms;
	uint16_t current = 0;
	std::mt19937 gen{std::random_device{}()};

	RandomMachine(T min, T max) { fill(min, max); }

	RandomMachine() { fill(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max()); }

	T next()
	{
		if (current >= PREGENERATED_RANDOM_SIZE)
			current = 0;
		return randoms[current++];
	}

	void fill(T min, T max)
	{
		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<T> dis(min, max);
			for (auto &r : randoms)
				r = dis(gen);
		}
		else if constexpr (std::is_floating_point_v<T>)
		{
			std::uniform_real_distribution<T> dis(min, max);
			for (auto &r : randoms)
				r = dis(gen);
		}
		else
		{
			static_assert(std::is_arithmetic_v<T>, "T must be numeric");
		}
	}
};

template <typename E>
struct RandomEnumMachine
{
    using EU = typename std::underlying_type<E>::type; 
    static constexpr uint16_t PREGENERATED_RANDOM_SIZE = 15000;
    std::array<EU, PREGENERATED_RANDOM_SIZE> randoms;
    uint16_t current = 0;
    std::mt19937 gen{std::random_device{}()};

    RandomEnumMachine(E min, E max)
    {
        std::uniform_int_distribution<EU> dis(
            static_cast<EU>(min),
            static_cast<EU>(max)
        );

        for (size_t i = 0; i < PREGENERATED_RANDOM_SIZE; i++)
            randoms[i] = dis(gen);
    }

    RandomEnumMachine()
    {
        std::uniform_int_distribution<EU> dis(
            static_cast<EU>(E::NONE),
            static_cast<EU>(E::MAX)
        );

        for (size_t i = 0; i < PREGENERATED_RANDOM_SIZE; i++)
            randoms[i] = dis(gen);
    }

    E next()
    {
        if (current >= PREGENERATED_RANDOM_SIZE) current = 0;
        return static_cast<E>(randoms[current++]);
    }
};

RandomEnumMachine<Direction> *random_direction =
    new RandomEnumMachine<Direction>(Direction::North, Direction::West);

struct RandomChanceMachine
{
	RandomMachine<float> mac = RandomMachine<float>(0.0, 1.0);
	RandomChanceMachine() {}

	float next() { return mac.next(); }
};

RandomChanceMachine *random_chance = new RandomChanceMachine();

struct RandomBoolMachine
{
	RandomMachine<int> mac = RandomMachine<int>(0, 1);
	bool next() { return mac.next(); }
};

RandomBoolMachine *random_bool = new RandomBoolMachine();

inline double rnormal()
{
	double u, v, s;
	do
	{
		u = 2.0 * (double)rand() / RAND_MAX - 1.0;
		v = 2.0 * (double)rand() / RAND_MAX - 1.0;
		s = u * u + v * v;
	} while (s >= 1.0 || s == 0.0);
	return u * sqrt(-2.0 * log(s) / s);
}
