#pragma once
#include <array>
#include <cstdint>

constexpr int CHUNK_LENGTH = 64;
constexpr int CHUNK_SIZE = CHUNK_LENGTH * CHUNK_LENGTH;
constexpr int CHUNKS_PER_REGION = 4;
constexpr uint16_t LATITUDE_TOTAL = 180;
constexpr int LATITUDE_MIN = -90;
constexpr int LATITUDE_MAX = 90;
constexpr int LONGITUDE_TOTAL = 180;

// time zones are in LST
constexpr uint16_t TIME_ZONES = 24;

inline constexpr std::array<float, TIME_ZONES> hour_angles{-180, -165, -150, -135, -120, -105, -90, -75,
					 -60,  -45,  -30,  -15,	 0,    15,   30,  45,
					 60,   75,   90,   105,	 120,  135,  150, 165};


