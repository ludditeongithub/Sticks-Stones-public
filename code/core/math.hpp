// RANDOM

#include <cstdlib>
#include <random>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>
#include <functional>
#include "structs.hpp"


    static std::random_device rd;
    static std::mt19937 gen(rd());

float rfloat(float min, float max) {
  
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

int rint(int min, int max) {
    if (min > max) std::swap(min, max); 

    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}


int rbin() {
    static std::uniform_int_distribution<int> dist(0, 1);
    return dist(gen);
}

bool rbool() {
    if (rbin() == 0) return false;
    return true;
}

bool rchance(double chance) {
    std::bernoulli_distribution dist(chance);
    return dist(gen);
}

double rnormal() {
    double u, v, s;
    do {
        u = 2.0 * (double)rand() / RAND_MAX - 1.0;
        v = 2.0 * (double)rand() / RAND_MAX - 1.0;
        s = u*u + v*v;
    } while(s >= 1.0 || s == 0.0);
    return u * sqrt(-2.0 * log(s) / s);
}


template<typename E>
E random_enum()
{
    using U = std::underlying_type_t<E>;
    std::uniform_int_distribution<U> dist(
        static_cast<U>(E::NONE) + 1,
        static_cast<U>(E::MAX) - 1
    );
    return static_cast<E>(dist(gen));
}


struct Percentage {
    double value;

    explicit Percentage(double v) : value(v) {
        if (v < 0.0 || v > 1.0) {
            throw std::out_of_range("Percentage must be between 0.0 and 1.0");
        }
    }
};

// Distance and Coords
template <typename T>
T chebyshev(T x1, T y1, T x2, T y2) {
    return std::max(std::abs(x2 - x1), std::abs(y2 - y1));
}

template <typename T>
T euclideanDist(T x1, T y1, T x2, T y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
  
uint16_t manhattanDist(int x1, int x2, int y1, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
};

uint16_t manhattanDist(Coord c1, Coord c2) {
  return abs(c1.x - c2.x) + abs(c1.y - c2.y);
};

template <typename T> inline float diffMult(T value, T target, T bound) {
  T range = std::abs(bound - target);
  T diff = std::abs(bound - value);
  return diff / range;
}

uint16_t coordToIndex(Coord c, int width) {
  return c.y * width + c.x;
};

uint16_t getIndex(uint16_t x, uint16_t y) {
  return x * width + y;
};

// Custom hash function for pair<int, int>
struct hashPair {
    std::size_t operator() (const std::pair<int, int>& p) const {
        auto h1 = std::hash<int>{}(p.first);
        auto h2 = std::hash<int>{}(p.second);
        return h1 ^ h2;  // Combine the two hash values
    }
};

std::size_t hashCoords(int x, int y) {
    auto h1 = std::hash<int>{}(x);
    auto h2 = std::hash<int>{}(y);
    return h1 ^ h2;  // Same hash mixing logic as in the struct
}
