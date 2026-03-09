#ifndef CHUNK_MANAGER_HPP
#define CHUNK_MANAGER_HPP
#include <cstdint>
#include <core/data.hpp>
#include <core/containers.hpp>

struct ChunkManager {
  uint16_t count;
  Array<Temp> temperatures;
  Array<Hum> humidities;
  
  ChunkManager(uint16_t count) : count(count), temperatures(count), humidities(count) {
}
  Temp getChunkTemperature(uint16_t index) {
    return temperatures[index];
  }    
};


#endif
