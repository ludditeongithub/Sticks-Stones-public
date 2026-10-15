#pragma once

#include <cstdint>

enum class Weather : uint8_t
{
	Clear,
	LightClouds,
	HeavyClouds,
	LightPrecipitation,
	MediumPrecipitation,
	HeavyPrecipitation,
	Heatwave,
};

using Hum = uint16_t;
using Temp = uint16_t;
using Alt = uint8_t;
using Liquid = uint16_t;
using Snow = uint16_t;
using WeatherValue = uint8_t;

using CloudKey = uint8_t;
using PrecipitationKey = uint8_t;
enum class PrecipitationType {
  Rain,
  Snow
};

struct Precipitation
  {
    Liquid liquid;
    PreciptationType type;
  }


