#ifndef TAGS_HPP
#define TAGS_HPP
#include "enum.hpp"
#include <core/tables.hpp>
#include <core/fbitset.hpp>
#include <cstdint>

// TODO:: sieve, which can separte sand and clay in, liquids and soil, etc
enum class itemTags : uint16_t
{
	NONE = 0,
	Resource = 1 << 0,
	Variant = 1 << 1,
	Alternate = 1 << 2,
	Liquid = 1 << 3,
	VariableAmountProduced = 1 << 4,
	VariableAmountsRequired = 1 << 5,
	FromCorpse = 1 << 6,
	RequiresUniqueVariant = 1 << 7,
	OptionalIngredient = 1 << 8,
	Tool = 1 << 9,
	Container = 1 << 10,
	// TODO: add flammable tags
	Mould = 1 << 11,
	Wearable = 1 << 12,
	Perishable = 1 << 13,
	WaterDamage = 1 << 14,
	Art = 1 << 15,
};

inline itemTags operator|(itemTags a, itemTags b)
{
	return static_cast<itemTags>(static_cast<std::underlying_type_t<itemTags>>(a) |
				     static_cast<std::underlying_type_t<itemTags>>(b));
}

inline itemTags &operator|=(itemTags &a, itemTags b)
{
	a = a | b;
	return a;
}

inline itemTags operator&(itemTags a, itemTags b)
{
	return static_cast<itemTags>(static_cast<std::underlying_type_t<itemTags>>(a) &
				     static_cast<std::underlying_type_t<itemTags>>(b));
}

inline bool hasTag(itemTags value, itemTags tag)
{
	return static_cast<std::underlying_type_t<itemTags>>(value & tag) != 0;
}


inline constexpr LookupTable<Item, itemTags> itemTags = []
{	
	LookupTable<Item,itemTags> lt{};
	using enum Item;
	lt[Item::Salt] = itemTags::Liquid;
	lt[Item::Flour] = itemTags::Perishable | itemTags::WaterDamage;
	lt[Item::MilledRice] = itemTags::Perishable;
	lt[Item::Bread] = itemTags::Perishable | itemTags::WaterDamage;
	lt[Item::Pastry] =
	    itemTags::OptionalIngredient | itemTags::Perishable | itemTags::WaterDamage;
	lt[Item::Pie] = itemTags::OptionalIngredient | itemTags::Perishable | itemTags::WaterDamage;
	lt[Item::Porridge] =
	    itemTags::OptionalIngredient | itemTags ::Perishable | itemTags::WaterDamage;
	lt[Item::RawMeat] = itemTags::Perishable;
	lt[Item::CookedMeat] = itemTags::Perishable;
	lt[Item::AnimalFat] = itemTags::Perishable;
	lt[Item::Cheese] = itemTags::Perishable;
	lt[Item::GoatCheese] = itemTags::Perishable;
	lt[Item::BlueCheese] = itemTags::Perishable;
	lt[Item::Beer] = itemTags::Liquid | itemTags::Perishable;
	lt[Item::Wine] = itemTags::Liquid | itemTags::RequiresUniqueVariant | itemTags::Perishable;
	lt[Item::FruitWine] = itemTags::Liquid | itemTags::Variant | itemTags::Perishable;
	lt[Item::Mead] = itemTags::Liquid | itemTags::Perishable;
	lt[Item::Vinegar] = itemTags::Liquid | itemTags::Perishable;
	lt[Item::Butter] = itemTags::Liquid | itemTags::Perishable;
	lt[Item::OliveOil] = itemTags::Liquid | itemTags::Perishable;
	lt[Item::CookingOil] =
	    itemTags::Liquid | itemTags::VariableAmountProduced | itemTags::Perishable;
	lt[Item::DrinkingWater] = itemTags::Liquid;
	lt[Item::Juice] = itemTags::Liquid | itemTags::Perishable;
	lt[Item::CandiedFruit] = itemTags::Perishable;
	lt[Item::AgedAlcoholicDrink] = itemTags::Perishable;
	lt[Item::SugarJuice] = itemTags::Liquid | itemTags::Perishable;
	lt[Item::Sugar] = itemTags::Perishable;
	lt[Item::GroundBlackPepper] = itemTags::Perishable;
	lt[Item::ChiliPowder] = itemTags::Perishable;
	lt[Item::Metal] = itemTags::VariableAmountsRequired | itemTags::VariableAmountProduced;
	lt[Item::Timber] = itemTags::VariableAmountProduced;
	lt[Item::Daub] = itemTags::VariableAmountProduced;
	lt[Item::Cob] = itemTags::VariableAmountProduced;
	lt[Item::PackedEarth] = itemTags::Alternate;
	lt[Item::Lime] = itemTags::RequiresUniqueVariant;
	lt[Item::Plaster] = itemTags::Liquid;
	lt[Item::CrushedStone] =
	    itemTags::VariableAmountsRequired | itemTags::VariableAmountProduced;
	lt[Item::Concrete] = itemTags::VariableAmountProduced | itemTags::Liquid;
	lt[Item::Mortar] = itemTags::Liquid;
	lt[Item::Glass] = itemTags::VariableAmountProduced | itemTags::VariableAmountsRequired;
	lt[Item::Glass] = itemTags::VariableAmountsRequired;
	lt[Item::Pane] = itemTags::VariableAmountProduced | itemTags::VariableAmountsRequired;
	lt[Item::FiredClay] = itemTags::Liquid | itemTags::VariableAmountProduced;
	lt[Item::Charcoal] = itemTags::VariableAmountProduced | itemTags::VariableAmountsRequired;
	lt[Item::Bone] = itemTags::FromCorpse;
	lt[Item::AnimalHair] =
	    itemTags::FromCorpse | itemTags::VariableAmountProduced | itemTags::Perishable;
	lt[Item::AnimalHides] = itemTags::FromCorpse | itemTags::VariableAmountProduced;
	lt[Item::Soot] = itemTags::VariableAmountsRequired |
			 // itemTags::VariableAmountProduced;
			 lt[Item::TanningAgent] =
			     itemTags::VariableAmountProduced | itemTags::Perishable;
	lt[Item::Nail] = itemTags::OptionalIngredient | itemTags::VariableAmountProduced;
	lt[Item::NailHeader] = itemTags::Mould;
	lt[Item::Glue] = itemTags::WaterDamage;
	lt[Item::String] = itemTags::VariableAmountProduced | itemTags::VariableAmountsRequired;
	lt[Item::Axle] = itemTags::Alternate;
	lt[Item::Gear] = itemTags::Alternate;
	lt[Item::SolidWheel] = itemTags::Alternate;
	lt[Item::Tube] = itemTags::Alternate;
	lt[Item::Peg] = itemTags::Alternate;
	lt[Item::Wedge] = itemTags::VariableAmountProduced;
	lt[Item::SmallHandle] = itemTags::VariableAmountProduced | itemTags::Alternate;
	lt[Item::LargeHandle] = itemTags::Alternate;
	lt[Item::BrickMold] = itemTags::Mould;
	lt[Item::MetalArrowhead] = itemTags::Alternate;
	lt[Item::ArrowShaft] = itemTags::Alternate;
	lt[Item::Trigger] = itemTags::VariableAmountsRequired;
	lt[Item::PrimitiveString] = itemTags::WaterDamage;
	lt[Item::RedDye] = itemTags::Alternate | itemTags::Liquid;
	lt[Item::YellowDye] = itemTags::Alternate | itemTags::Liquid;
	lt[Item::BlueDye] = itemTags::Alternate | itemTags::Liquid;
	lt[Item::Bleach] = itemTags::Liquid;
	lt[Item::Ink] = itemTags::Liquid;
	lt[Item::Incense] = itemTags::Perishable;
	lt[Item::Paper] = itemTags::WaterDamage;
	lt[Item::Laxative] = itemTags::Alternate;
	lt[Item::Tonic] = itemTags::Alternate | itemTags::Liquid;
	lt[Item::BoneMeal] = itemTags::Perishable;
	lt[Item::FishMeal] = itemTags::Perishable;
	lt[Item::Fertilizer] = itemTags::Perishable;
	lt[Item::CoinMould] = itemTags::Alternate;
	lt[Item::PrimitiveSpearHead] = itemTags::Alternate;
	lt[Item::KnifeHead] = itemTags::Alternate;
	lt[Item::SickleHead] = itemTags::Alternate;
	lt[Item::AwlHead] = itemTags::Alternate;
	lt[Item::AdzeHead] = itemTags::Alternate;
	lt[Item::MalletHead] = itemTags::Alternate;
	lt[Item::ScalpelHead] = itemTags::Alternate;
	lt[Item::HammerHead] = itemTags::Alternate;
	lt[Item::ChiselHead] = itemTags::Alternate;
	lt[Item::TrowelHead] = itemTags::Alternate;
	lt[Item::CleaverHead] = itemTags::Alternate;
	lt[Item::MacheteHead] = itemTags::Alternate;
	lt[Item::SwordHead] = itemTags::Alternate;
	lt[Item::HandaxeHead] = itemTags::Alternate;
	lt[Item::PermanentKnifeHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentSickleHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentAwlHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentAdzeHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentMalletHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentScalpelHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentHammerHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentChiselHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentTrowelHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentCleaverHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentMacheteHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentSwordHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PermanentHandaxeHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PrimitiveSpearHead] = itemTags::Alternate;
	lt[Item::ScytheHead] = itemTags::Alternate;
	lt[Item::PermanentScytheHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::ArdHead] = itemTags::Alternate;
	lt[Item::PermanentArdHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::HeavySawHead] = itemTags::Alternate;
	lt[Item::PermanentHeavySawHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::SawHead] = itemTags::Alternate;
	lt[Item::PermanentSawHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::ShovelHead] = itemTags::Alternate;
	lt[Item::PermanentShovelHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::AxeHead] = itemTags::Alternate;
	lt[Item::PermanentAxeHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PickaxeHead] = itemTags::Alternate;
	lt[Item::PermanentPickaxeHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::GreatswordHead] = itemTags::Alternate;
	lt[Item::PermanentGreatswordHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::GreataxeHead] = itemTags::Alternate;
	lt[Item::PermanentGreataxeHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::HalberdHead] = itemTags::Alternate;
	lt[Item::PermanentHalberdHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::PikeHead] = itemTags::Alternate;
	lt[Item::PermanentPikeHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::SpearHead] = itemTags::Alternate;
	lt[Item::PermanentSpearHeadMould] = itemTags::Alternate | itemTags::Mould;
	lt[Item::Cloth] = itemTags::WaterDamage;
	lt[Item::DyedCloth] = itemTags::WaterDamage;
	lt[Item::Tribalwear] = itemTags::Wearable;
	lt[Item::BasicClothes] = itemTags::Wearable;
	lt[Item::FormalClothes] = itemTags::VariableAmountRequired | itemTags::Wearable;
	lt[Item::FancyClothes] = itemTags::VariableAmountRequired | itemTags::Wearable;
	lt[Item::GoldCrown] = itemTags::Wearable;
	lt[Item::RoyalCrown] = itemTags::Wearable;
	lt[Item::Necklace] = itemTags::Wearable;
	lt[Item::Ring] = itemTags::Alternate | itemTags::Wearable;
	lt[Item::Earring] = itemTags::Alternate | itemTags::Wearable;
	lt[Item::Gambeson] = itemTags::Wearable;
	lt[Item::DrawPlate] = itemTags::Mould;
	lt[Item::Chainmail] = itemTags::Wearable;
	lt[Item::Helmet] = itemTags::Alternate | itemTags::Wearable;
	lt[Item::Breastplate] = itemTags::Alternate | itemTags::Wearable;
	lt[Item::Guards] = itemTags::Alternate | itemTags::Wearable;
	lt[Item::Bracers] = itemTags::Alternate | itemTags::Wearable;
	lt[Item::Gloves] = itemTags::Wearable;
	lt[Item::Apron] = itemTags::Wearable;
	lt[Item::Sandals] = itemTags::Wearable;
	lt[Item::Boots] = itemTags::Wearable;
	lt[Item::Cape] = itemTags::Wearable;
	lt[Item::Javelin] = itemTags::Alternate;
	lt[Item::PitFire] = itemTags::VariableAmountRequired | itemTags::WaterDamage;
	lt[Item::Torch] = itemTags::WaterDamage;
	lt[Item::CandleMould] = itemTags::Alternate;
	lt[Item::Candle] = itemTags::Alternate | itemTags::Wearable | itemTags::WaterDamage;
	lt[Item::OilLamp] = itemTags::Alternate | itemTags::WaterDamage;
}();
#endif
