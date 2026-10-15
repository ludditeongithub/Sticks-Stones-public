#pragma once

#include <cstdint>
#include <data/types/geography.hpp>
#include <core/containers.hpp/>
#include <data/types/entity.hpp>

namespace weather {

// @codegen:begin weather
constexpr static uint16_t SIZE =  0
+ sizeof(Temp) 
+ sizeof(Hum) 
+ sizeof(Precipitation) 
;

size_t capacity;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Temp> diurnal_temp_variances;
    Array<Hum> diurnal_hum_variances;
    Array<Precipitation> current_precipitations;


// =========================
// INIT
// =========================

  void init(Arena* arena, size_t cap) 
{
capacity = cap;
 
  diurnal_temp_variances = arena_make_array<Temp>(arena, capacity);
 
  diurnal_hum_variances = arena_make_array<Hum>(arena, capacity);
 
  current_precipitations = arena_make_array<Precipitation>(arena, capacity);
 

}
    // =========================
    // SERIALIZATION
    // =========================

      template <class Archive>
    void serialize(Archive &archive)
   {
           diurnal_temp_variances.serialize(archive);
           diurnal_hum_variances.serialize(archive);
           current_precipitations.serialize(archive);
         
    }
         
// =========================
// GETTERS
// =========================

  inline Temp& diurnal_temp_variance(const EntityID index) {
return diurnal_temp_variances[index];
  }
  inline Hum& diurnal_hum_variance(const EntityID index) {
return diurnal_hum_variances[index];
  }
  inline Precipitation& current_precipitation(const EntityID index) {
return current_precipitations[index];
  }

// @codegen:end weather
};
