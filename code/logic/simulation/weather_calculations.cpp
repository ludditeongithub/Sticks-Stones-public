#include <cmath>
#include <core/math.hpp>
#include <numbers>
#include <core/containers.hpp>
#include <data/const/chunk_data.hpp>
#include <data/run/world.hpp>
#include <data/const/environment_data.hpp>

void World::calculate_chunk_temperature_inputs(Array<int8_t> &water_bodies_dists)
{
	// calculate season based on orbit
	for (int i = 0; i < static_cast<int>(chunk_amount); i++)
	{
		float humidity_factor = humidities[i] / MAX_HUMIDITY;
		// TODO: have hadley cells factor
		float latitude_factor = unsigned_abs_diff(equator , get_chunk_height(i)) / equator;
		float altitude_factor =
		    std::fmin(1.0, 1.0 - ((MAX_ALTITUDE - altitudes[i]) / MAX_ALTITUDE));
		float water_bodies_proximity_factor =
		    std::fmin(1.0, 1.0 - (MAX_OCEAN_AFFECT_DIST - water_bodies_dists[i] / MAX_OCEAN_AFFECT_DIST));

		float df = std::lerp(humidity_factor, latitude_factor, 0.4f);
		float ds = std::lerp(df, altitude_factor, 0.3f);
		float dt = std::lerp(ds, water_bodies_proximity_factor, 0.08f);
		temp::diurnal_temp_variances[i] = MAX_DIURNAL_VAR * dt;

		float ss = std::lerp(latitude_factor, water_bodies_proximity_factor, 0.4f);
		float st = std::lerp(ss, altitude_factor, 0.08f);
		temp::seasonal_temp_variances[i] = MAX_SEASONAL_VAR * st;

		// TODO: check
		temp::min_temps[i] = temperatures[i] - (temp::seasonal_temp_variances[i] + temp::diurnal_temp_variances[i]);
	}
}

// Arena<float> calculate_sunset_hour_angles(int day365) {
//   Arena<float> sunset_hour_angles(LATITUDE_TOTAL);

//  float solar_declination =
//       23.44f *
//       std::sin((2 * std::numbers::pi_v<float> / 365.0f) * (day365 - 80));
//  float solar_declination_rad =
//      solar_declination * std::numbers::pi_v<float> / 180.0f;

// for (auto i = LATITUDE_MIN; i < LATITUDE_MAX; i++) {
//           float lat_rad = i * std::numbers::pi_v<float> / 180.0f;
//         float cos_h0 = -std::tan(lat_rad) * std::tan(solar_declination_rad);
//         if (cos_h0 < -1.0f) cos_h0 = -1.0f;
//         if (cos_h0 >  1.0f) cos_h0 =  1.0f;

//         float H0 = std::acosf(cos_h0);

//         float H0Deg = H0 * 180.0f / std::numbers::pi_v<float>;
// 	sunset_hour_angles[i] = H0Deg;
// }
//  return sunset_hour_angles;
// }

// Arena<int> calculate_day_lengths(Arena<float>& sunset_hour_angles) {
//   Arena<int> day_lengths(CHUNK_AMOUNT);

//     for (int i = LATITUDE_MIN; i <= LATITUDE_MAX; i++) {
//         day_lengths[i] = (2.0f * sunset_hour_angles[i]) / 15.0f;
//     }
//     return day_lengths;
// }

// insolations are normalized to be between 0 and 1.
Array<float> calculate_seasonal_insolations(int day365)
{
	Array<float> insolations(static_cast<uint32_t>(LATITUDE_TOTAL));

	float solar_declination =
	    23.44f * std::sin((2 * std::numbers::pi_v<float> / 365.0f) * (day365 - 80));
	float solar_declination_rad = solar_declination * std::numbers::pi_v<float> / 180.0f;

	for (auto i = 0; i < LATITUDE_TOTAL; i++)
	{
		float latitude = -90.0f + i * (180.0f / (LATITUDE_TOTAL - 1));
		float latitude_rad = latitude * std::numbers::pi_v<float> / 180.0f;
		insolations[i] = 2.0f * std::cos(latitude_rad - solar_declination_rad) - 1.0f;
	}
	return insolations;
}

// TODO: ensure that there is some thermal lag (doen't normalize hour angle)
void World::update_daily_insolations(uint16_t day365)
{
	float solar_declination =
	    23.44f * std::sin((2 * std::numbers::pi_v<float> / 365.0f) * (day365 - 80));


	for (auto i = LATITUDE_MIN; i < LATITUDE_MAX; i++)
	{
		for (int j = 0; j < TIME_ZONES; j++)
		{
			float s = sin(i) * sin(solar_declination);
			float c = cos(i) * cos(solar_declination);
			float cos_time = s + (c * cos(hour_angles[j]));
			float cos_max = s + c;
			daily_insolations[i][j] = std::fmax(0.0, (cos_time / cos_max));
		}
	}
}

void World::update_chunk_temperature()
{
	for (int i = 0; i < chunk_amount; i++)
	{
		float latitude = get_chunk_latitude(i);
		float time_zone = get_chunk_time_zone(i);
		float sv = temp::seasonal_temp_variances[i] * seasonal_insolations[latitude];
		float dv = temp::diurnal_temp_variances[i] * daily_insolations[latitude][time_zone];
		temperatures[i] =
		    temp::min_temps[i] + (sv + dv / 1 + (cloud_covers[i] * MAX_CLOUD_FACTOR));
	}
}

void World::calculate_chunk_precipitation_equilibrium()
{
	for (size_t i = 0; i < chunk_amount; i++) precipitation_cores[i] = humidities[i] * 	
}
