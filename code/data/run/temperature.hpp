#pragma once
#include <core/containers.hpp>
#include <data/types/entity.hpp>

namespace temp
{
  // @codegen:begin temp
constexpr static uint16_t SIZE =  0
+ sizeof(float) 
+ sizeof(float) 
+ sizeof(float) 
;

size_t capacity;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<float> min_temps;
    Array<float> diurnal_temp_variances;
    Array<float> seasonal_temp_variances;


// =========================
// INIT
// =========================

  void init(Arena* arena, size_t cap) 
{
capacity = cap;
 
  min_temps = arena_make_array<float>(arena, capacity);
 
  diurnal_temp_variances = arena_make_array<float>(arena, capacity);
 
  seasonal_temp_variances = arena_make_array<float>(arena, capacity);
 

}
    // =========================
    // SERIALIZATION
    // =========================

      template <class Archive>
    void serialize(Archive &archive)
   {
           min_temps.serialize(archive);
           diurnal_temp_variances.serialize(archive);
           seasonal_temp_variances.serialize(archive);
         
    }
         
// =========================
// GETTERS
// =========================

  inline float& min_temp(const EntityID index) {
return min_temps[index];
  }
  inline float& diurnal_temp_variance(const EntityID index) {
return diurnal_temp_variances[index];
  }
  inline float& seasonal_temp_variance(const EntityID index) {
return seasonal_temp_variances[index];
  }

  // @codegen:end temp
}
