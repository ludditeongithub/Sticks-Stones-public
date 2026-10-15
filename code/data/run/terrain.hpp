#pragma once

#include <cstdint>
#include <data/types/geography.hpp>
#include <core/memory.hpp>
#include <core/containers.hpp>
#include <data/types/entity.hpp>

namespace terrain {

// @codegen:begin terrain
constexpr static uint16_t SIZE =  0
+ sizeof(Alt) 
+ sizeof(Liquid) 
+ sizeof(Snow) 
;

size_t capacity;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Alt> altitudes;
    Array<Liquid> liquids;
    Array<Snow> snows;


// =========================
// INIT
// =========================

  void init(Arena* arena, size_t cap) 
{
capacity = cap;
 
  altitudes = arena_make_array<Alt>(arena, capacity);
 
  liquids = arena_make_array<Liquid>(arena, capacity);
 
  snows = arena_make_array<Snow>(arena, capacity);
 

}
    // =========================
    // SERIALIZATION
    // =========================

      template <class Archive>
    void serialize(Archive &archive)
   {
           altitudes.serialize(archive);
           liquids.serialize(archive);
           snows.serialize(archive);
         
    }
         
// =========================
// GETTERS
// =========================

  inline Alt& altitude(const EntityID index) {
return altitudes[index];
  }
  inline Liquid& liquid(const EntityID index) {
return liquids[index];
  }
  inline Snow& snow(const EntityID index) {
return snows[index];
  }

// @codegen:end terrain
};
