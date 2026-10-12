#include "data/types/unit.hpp"
#include <data/types/stats.hpp>
#include <data/types/combat.hpp>
#include "data/const/tags.hpp"
#include <data/const/unit_data.hpp>

template<typename T>
float get_skill_factor(T skill, float skill_relevance)
{
  float dif = skill / STAT_MAX;
  return lerp(DEFAULT_SKILL_FACTOR, MAX_SKILL_FACTOR * dif, skill_relevance);
}

float get_attacking_skill_factor(Skills& skills, WeaponAttackData& weapon_data)
{
  float sf = get_skill_factor(skills.strength, weapon_data.strength_factor);
  float af = get_skill_factor(skills.athleticism, weapon_data.athleticism_factor);
  float df = get_skill_factor(skills.dexterity, weapon_data.dexterity_factor);
  float pf = get_skill_factor(skills.perception, weapon_data.perception_factor);
  return 1.0 * sf * af * df * pf;
}

float get_defending_skill_factor(Skills& skills, ArmorSkillData& armor_data)
{
  float sf = get_skill_factor(skills.strength, armor_data.strength_factor);
  float af = get_skill_factor(skills.athleticism, armor_data.athleticism_factor);
  float df = get_skill_factor(skills.dexterity, armor_data.dexterity_factor);
  float pf = get_skill_factor(skills.perception, armor_data.perception_factor);
  return 1.0 * sf * af * df * pf;  
}

// 0 means no hit
Health get_hit(float miss_chance, Item weapon, Skills& attacker_skills, Skills& defender_skills, Item armor, uint16_t range)
{
	assert(has_tag(weapon, item::Tag::TwoHandedTool) ||
	  has_tag(weapon, item::Tag::OneHandedTool) && has_tag(armor, item::Tag::Wearable));
	WeaponAttackData wad = item::WEAPON_ATTACK_DATAS[weapon];
	assert(range < wad.max_range);	
	float asf = get_attacking_skill_factor(attacker_skills, wad);        
  
	ArmorSkillData asd = item::ARMOR_SKILL_DATAS[armor];
	float dsf = get_defending_skill_factor(defender_skills, asd);

        // TODO: weak blows, strong blows
	if (wad.default_hit_chance * asf > miss_chance * dsf)
	  return wad.damage;
        else return 0;
}


