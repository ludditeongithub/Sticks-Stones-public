#pragma once
#include <cstdint>
inline uint32_t hash_pair(uint16_t a, uint16_t b) { return (static_cast<uint32_t>(a) << 16) | b; }
