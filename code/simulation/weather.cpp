#include <cmath>
#include <core/math.hpp>
#include <numbers>
#include <core/containers.hpp>
#include <world/chunk/data.hpp>
#include <world/world.hpp>

void World::calculateChunkTemperatureInputs(ChunkTempData &cd, Array<Hum> &humidities, Array<Alt> &altitudes, Array<int8_t> &waterBodiesDists, Array<Temp> &temperatures)
{
	// calculate season based on orbit
	for (int i = 0; i < static_cast<int>(CHUNK_AMOUNT); i++)
	{
		float humidityFactor = humidities[i] / MAX_HUMIDITY;
		// TODO: have hadley cells factor
		float latitudeFactor = abs(EQUATOR - getChunkHeight(i)) / EQUATOR;
		float altitudeFactor =
		    std::fmin(1.0, 1.0 - ((MAX_ALTITUDE - altitudes[i]) / MAX_ALTITUDE));
		float waterBodiesProximityFactor =
		    std::fmin(1.0, 1.0 - (MAX_OCEAN_AFFECT_DIST -
					  waterBodiesDists[i] / MAX_OCEAN_AFFECT_DIST));

		float df = std::lerp(humidityFactor, latitudeFactor, 0.4f);
		float ds = std::lerp(df, altitudeFactor, 0.3f);
		float dt = std::lerp(ds, waterBodiesProximityFactor, 0.08f);
		cd.diurnalTempVariances[i] = MAX_DIURNAL_VAR * dt;

		float ss = std::lerp(latitudeFactor, waterBodiesProximityFactor, 0.4f);
		float st = std::lerp(ss, altitudeFactor, 0.08f);
		cd.seasonalTempVariances[i] = MAX_SEASONAL_VAR * st;

		// TODO: check
		cd.minTemps[i] = temperatures[i] - (cd.seasonalTempVariances[i] + cd.diurnalTempVariances[i]);
	}
}

// Arena<float> calculateSunsetHourAngles(int day365) {
//   Arena<float> sunsetHourAngles(LATITUDE_TOTAL);

//  float solarDeclination =
//       23.44f *
//       std::sin((2 * std::numbers::pi_v<float> / 365.0f) * (day365 - 80));
//  float solarDeclinationRad =
//      solarDeclination * std::numbers::pi_v<float> / 180.0f;

// for (auto i = LATITUDE_MIN; i < LATITUDE_MAX; i++) {
//           float latRad = i * std::numbers::pi_v<float> / 180.0f;
//         float cosH0 = -std::tan(latRad) * std::tan(solarDeclinationRad);
//         if (cosH0 < -1.0f) cosH0 = -1.0f;
//         if (cosH0 >  1.0f) cosH0 =  1.0f;

//         float H0 = std::acosf(cosH0);

//         float H0Deg = H0 * 180.0f / std::numbers::pi_v<float>;
// 	sunsetHourAngles[i] = H0Deg;
// }
//  return sunsetHourAngles;
// }

// Arena<int> calculateDayLengths(Arena<float>& sunsetHourAngles) {
//   Arena<int> dayLengths(CHUNK_AMOUNT);

//     for (int i = LATITUDE_MIN; i <= LATITUDE_MAX; i++) {
//         dayLengths[i] = (2.0f * sunsetHourAngles[i]) / 15.0f;
//     }
//     return dayLengths;
// }

// insolations are normalized to be between 0 and 1.
Array<float> calculateSeasonalInsolations(int day365)
{
	Array<float> insolations(static_cast<uint32_t>(LATITUDE_TOTAL));

	float solarDeclination =
	    23.44f * std::sin((2 * std::numbers::pi_v<float> / 365.0f) * (day365 - 80));
	float solarDeclinationRad = solarDeclination * std::numbers::pi_v<float> / 180.0f;

	for (auto i = 0; i < LATITUDE_TOTAL; i++)
	{
		float latitude = -90.0f + i * (180.0f / (LATITUDE_TOTAL - 1));
		float latitudeRad = latitude * std::numbers::pi_v<float> / 180.0f;
		insolations[i] = 2.0f * std::cos(latitudeRad - solarDeclinationRad) - 1.0f;
	}
	return insolations;
}

// TODO: ensure that there is some thermal lag (doen't normalize hour angle)
void World::updateDailyInsolations(uint16_t day365)
{
	float solarDeclination =
	    23.44f * std::sin((2 * std::numbers::pi_v<float> / 365.0f) * (day365 - 80));


	for (auto i = LATITUDE_MIN; i < LATITUDE_MAX; i++)
	{
		for (int j = 0; j < TIME_ZONES; j++)
		{
			float s = sin(i) * sin(solarDeclination);
			float c = cos(i) * cos(solarDeclination);
			float cosTime = s + (c * cos(hourAngles[j]));
			float cosMax = s + c;
			dailyInsolations[i][j] = std::fmax(0.0, (cosTime / cosMax));
		}
	}
}

void World::updateChunkTemperature()
{
	for (int i = 0; i < CHUNK_AMOUNT; i++)
	{
		float latitude = getChunkLatitude(i);
		float timeZone = getChunkTimeZone(i);
		float sv = chunkTempData.seasonalTempVariances[i] * seasonalInsolations[latitude];
		float dv = chunkTempData.diurnalTempVariances[i] * dailyInsolations[latitude][timeZone];
		temperatures[i] =
		    chunkTempData.minTemps[i] + (sv + dv / 1 + (cloudCovers[i] * MAX_CLOUD_FACTOR));
	}
}

void calculateChunkPrecipationEquilibrium() {}

void updateChunkPrecipitation() {}

// TODO: updatePrecipitationAmount
void updateChunkWeather() {}
