#include "world/tile/data.hpp"
#include <limits>
#include <random>
#include <array>
#include <type_traits>

constexpr uint16_t PREGENERATED_RANDOM_SIZE = 15000;
static std::random_device rd;
static std::mt19937 gen(rd());

template <typename T>
struct RandomMachine {
  std::array<T, PREGENERATED_RANDOM_SIZE> randoms;
	uint16_t current = 0;
	RandomMachine(T min, T max) {
          std::uniform_real_distribution<T> dis(min, max);
	  for (size_t i = 0; i < PREGENERATED_RANDOM_SIZE; i++) randoms[i] = dis(gen);
        }

        RandomMachine() {
		std::uniform_real_distribution<T> dis(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
	  for (size_t i = 0; i < PREGENERATED_RANDOM_SIZE; i++) randoms[i] = dis(gen);
        }

        T next() {
		if (current >= PREGENERATED_RANDOM_SIZE) current = 0;
		return randoms[current++];
	}
};

template <typename E> struct RandomEnumMachine {
	using EU = std::underlying_type<E>;
	 std::array<EU, PREGENERATED_RANDOM_SIZE> randoms;
	uint16_t current = 0;
	RandomEnumMachine(E min, E max) {
          std::uniform_real_distribution<EU> dis(
              std::underlying_type<EU>(min), std::underlying_type<EU>(max));
	  for (size_t i = 0; i < PREGENERATED_RANDOM_SIZE; i++) randoms[i] = dis(gen);
        }

        RandomEnumMachine() {
		std::uniform_real_distribution<EU> dis(static_cast<EU>(E::NONE), static_cast<EU>(E::MAX) );
	  for (size_t i = 0; i < PREGENERATED_RANDOM_SIZE; i++) randoms[i] = dis(gen);
	}
};

struct RandomChanceMachine {
	RandomMachine<float> mac = RandomMachine<float>(0.0,1.0);
        RandomChanceMachine() {}

        float next() {
		return mac.next();
	}
};

RandomChanceMachine* chance = new RandomChanceMachine();

inline double rnormal() {
    double u, v, s;
    do {
        u = 2.0 * (double)rand() / RAND_MAX - 1.0;
        v = 2.0 * (double)rand() / RAND_MAX - 1.0;
        s = u*u + v*v;
    } while(s >= 1.0 || s == 0.0);
    return u * sqrt(-2.0 * log(s) / s);
}

