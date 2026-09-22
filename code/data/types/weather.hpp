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
