#pragma once

std::array<uint16_t, 10> sight_ranges; // based on perception

inline uint16_t get_sight_range(Perception perception) {
	return 10 + (perception / 3);
}
