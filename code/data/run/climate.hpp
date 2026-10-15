#pragma once

namespace climate
  {
    // @codegen:begin climate
constexpr static uint16_t SIZE =  0
+ sizeof(Temp) 
+ sizeof(Temp) 
+ sizeof(Hum) 
+ sizeof(Hum) 
;

size_t capacity;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Temp> base_temps;
    Array<Temp> seasonal_temp_variances;
    Array<Hum> base_hums;
    Array<Hum> seasonal_hum_variances;


// =========================
// INIT
// =========================

  void init(Arena* arena, size_t cap) 
{
capacity = cap;
 
  base_temps = arena_make_array<Temp>(arena, capacity);
 
  seasonal_temp_variances = arena_make_array<Temp>(arena, capacity);
 
  base_hums = arena_make_array<Hum>(arena, capacity);
 
  seasonal_hum_variances = arena_make_array<Hum>(arena, capacity);
 

}
    // =========================
    // SERIALIZATION
    // =========================

      template <class Archive>
    void serialize(Archive &archive)
   {
           base_temps.serialize(archive);
           seasonal_temp_variances.serialize(archive);
           base_hums.serialize(archive);
           seasonal_hum_variances.serialize(archive);
         
    }
         
// =========================
// GETTERS
// =========================

  inline Temp& base_temp(const EntityID index) {
return base_temps[index];
  }
  inline Temp& seasonal_temp_variance(const EntityID index) {
return seasonal_temp_variances[index];
  }
  inline Hum& base_hum(const EntityID index) {
return base_hums[index];
  }
  inline Hum& seasonal_hum_variance(const EntityID index) {
return seasonal_hum_variances[index];
  }

// @codegen:end climate

  }
