#include "../include/basic.hpp"

//TODO: altitude -10 to 650
alt noiseToAltitude(float noiseValue) {
  noiseValue = std::clamp(noiseValue, -1.0 , 1.0);
  return ((noiseValue + 1.0) * altMax) - altMin;
}

