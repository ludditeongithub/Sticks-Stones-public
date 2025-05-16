#ifndef BASIC_H_
#define BASIC_H_

#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include <array>
#include <cmath>
#include <map>
#include <algorithm>
#include <random>
#include <queue>
#include <ctime>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include "FastNoiseLite.h"
#include "nanoflann.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::cout;
using std::endl;
using std::get;
using std::pair;
using std::unordered_map;

struct coord {
  int x;
  int y;
};

float rfloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

int rint(int min, int max) {
    if (min > max) std::swap(min, max); // Prevent crash on invalid input

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}


int rbin() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 1);
    return dist(gen); // Returns either 0 or 1
}

float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

int chebyshev(int x1, int y1, int x2, int y2) {
    return std::max(std::abs(x2 - x1), std::abs(y2 - y1));
}

float euclideanDist(float x1, float y1, float x2, float y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

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

enum class Direction {
    North, East, South, West
};

std::pair<int,int> newCoordsFromFacing(std::pair<int,int> coords, Direction direction) {
switch(direction) {
    case Direction::North:
        return {coords.first+1, coords.second};
    case Direction::East:
        return {coords.first, coords.second+1};
    case Direction::South:
        return {coords.first-1, coords.second};
    default:
        return {coords.first, coords.second-1};
}
}

struct SeedCloud {
    std::vector<std::pair<float, float>> seeds; // Using std::pair<float, float>

    // Must return the dimensionality of points (2D case: x, y)
    inline size_t kdtree_get_point_count() const { return seeds.size(); }

    // Return the dimension (0 = x, 1 = y) of a given index
    inline float kdtree_get_pt(const size_t idx, const size_t dim) const {
        return (dim == 0) ? seeds[idx].first : seeds[idx].second;
    }

    // Optional: Bounding box, not required
    template <class BBOX>
    bool kdtree_get_bbox(BBOX& /*bb*/) const { return false; }
};


#endif // BASIC_H_
