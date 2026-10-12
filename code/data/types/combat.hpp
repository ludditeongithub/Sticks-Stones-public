#pragma once
#include <cstdint>
#include <data/types/stats.hpp>

struct WeaponAttackData
{
  Health damage;
  float default_hit_chance;
  uint16_t max_range;
  
  float strength_factor;
  float athleticism_factor;
  float dexterity_factor;
  float perception_factor;  
};

struct ArmorSkillData
{  
  float strength_factor;
  float athleticism_factor;
  float dexterity_factor;
  float perception_factor;
};
