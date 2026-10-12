#pragma once
#include <core/tables.hpp>
#include <cstdint>
#include <core/tags.hpp>
#include <data/types/item.hpp>

namespace item
{

  // TODO:: sieve, which can separte sand and clay in, liquids and soil, etc
enum class Tag : uint32_t
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
	OneHandedTool = 1 << 9,
	Container = 1 << 10,
	Mould = 1 << 11,
	Wearable = 1 << 12,
	Perishable = 1 << 13,
	// TODO: sort from rust
	WaterDamage = 1 << 14,
	Art = 1 << 15,
	// TODO: add scavengeable tags
	Scavengeable = 1 << 16,
	// TODO: add flammable tags
	Flammable = 1 << 17,
	TwoHandedTool = 1 << 18,
	VisibleInHand = 1 << 19,	
};

inline const LookupTable<Item, Tag> TAGS = []
{	
	LookupTable<Item,Tag> lt{};
	lt[Item::Salt] = Tag::Liquid;
	lt[Item::Flour] = Tag::Perishable | Tag::WaterDamage;
	lt[Item::MilledRice] = Tag::Perishable;
	lt[Item::Bread] = Tag::Perishable | Tag::WaterDamage;
	lt[Item::Pastry] =
	    Tag::OptionalIngredient | Tag::Perishable | Tag::WaterDamage;
	lt[Item::Pie] = Tag::OptionalIngredient | Tag::Perishable | Tag::WaterDamage;
	lt[Item::Porridge] =
	    Tag::OptionalIngredient | Tag ::Perishable | Tag::WaterDamage;
	lt[Item::RawMeat] = Tag::Perishable;
	lt[Item::CookedMeat] = Tag::Perishable;
	lt[Item::AnimalFat] = Tag::Perishable;
	lt[Item::Cheese] = Tag::Perishable;
	lt[Item::GoatCheese] = Tag::Perishable;
	lt[Item::BlueCheese] = Tag::Perishable;
	lt[Item::Beer] = Tag::Liquid | Tag::Perishable;
	lt[Item::Wine] = Tag::Liquid | Tag::RequiresUniqueVariant | Tag::Perishable;
	lt[Item::FruitWine] = Tag::Liquid | Tag::Variant | Tag::Perishable;
	lt[Item::Mead] = Tag::Liquid | Tag::Perishable;
	lt[Item::Vinegar] = Tag::Liquid | Tag::Perishable;
	lt[Item::Butter] = Tag::Liquid | Tag::Perishable;
	lt[Item::OliveOil] = Tag::Liquid | Tag::Perishable;
	lt[Item::CookingOil] =
	    Tag::Liquid | Tag::VariableAmountProduced | Tag::Perishable;
	lt[Item::DrinkingWater] = Tag::Liquid;
	lt[Item::Juice] = Tag::Liquid | Tag::Perishable;
	lt[Item::CandiedFruit] = Tag::Perishable;
	lt[Item::AgedAlcoholicDrink] = Tag::Perishable;
	lt[Item::SugarJuice] = Tag::Liquid | Tag::Perishable;
	lt[Item::Sugar] = Tag::Perishable;
	lt[Item::GroundBlackPepper] = Tag::Perishable;
	lt[Item::ChiliPowder] = Tag::Perishable;
	lt[Item::Metal] = Tag::VariableAmountsRequired | Tag::VariableAmountProduced;
	lt[Item::Timber] = Tag::VariableAmountProduced;
	lt[Item::Daub] = Tag::VariableAmountProduced;
	lt[Item::Cob] = Tag::VariableAmountProduced;
	lt[Item::PackedEarth] = Tag::Alternate;
	lt[Item::Lime] = Tag::RequiresUniqueVariant;
	lt[Item::Plaster] = Tag::Liquid;
	lt[Item::CrushedStone] =
	    Tag::VariableAmountsRequired | Tag::VariableAmountProduced;
	lt[Item::Concrete] = Tag::VariableAmountProduced | Tag::Liquid;
	lt[Item::Mortar] = Tag::Liquid;
	lt[Item::Glass] = Tag::VariableAmountProduced | Tag::VariableAmountsRequired;
	lt[Item::Glass] = Tag::VariableAmountsRequired;
	lt[Item::Pane] = Tag::VariableAmountProduced | Tag::VariableAmountsRequired;
	lt[Item::FiredClay] = Tag::Liquid | Tag::VariableAmountProduced;
	lt[Item::Charcoal] = Tag::VariableAmountProduced | Tag::VariableAmountsRequired;
	lt[Item::Bone] = Tag::FromCorpse;
	lt[Item::AnimalHair] =
	    Tag::FromCorpse | Tag::VariableAmountProduced | Tag::Perishable;
	lt[Item::AnimalHides] = Tag::FromCorpse | Tag::VariableAmountProduced;
	lt[Item::Soot] = Tag::VariableAmountsRequired;
	// Tag::VariableAmountProduced;
	lt[Item::TanningAgent] = Tag::VariableAmountProduced | Tag::Perishable;
	lt[Item::Nail] = Tag::OptionalIngredient | Tag::VariableAmountProduced;
	lt[Item::NailHeader] = Tag::Mould;
	lt[Item::Glue] = Tag::WaterDamage;
	lt[Item::String] = Tag::VariableAmountProduced | Tag::VariableAmountsRequired;
	lt[Item::Axle] = Tag::Alternate;
	lt[Item::Gear] = Tag::Alternate;
	lt[Item::SolidWheel] = Tag::Alternate;
	lt[Item::Tube] = Tag::Alternate;
	lt[Item::Peg] = Tag::Alternate;
	lt[Item::Wedge] = Tag::VariableAmountProduced;
	lt[Item::SmallHandle] = Tag::VariableAmountProduced | Tag::Alternate;
	lt[Item::LargeHandle] = Tag::Alternate;
	lt[Item::BrickMould] = Tag::Mould;
	lt[Item::ArrowShaft] = Tag::Alternate;
	lt[Item::Trigger] = Tag::VariableAmountsRequired;
	lt[Item::PrimitiveString] = Tag::WaterDamage;
	lt[Item::RedDye] = Tag::Alternate | Tag::Liquid;
	lt[Item::YellowDye] = Tag::Alternate | Tag::Liquid;
	lt[Item::BlueDye] = Tag::Alternate | Tag::Liquid;
	lt[Item::Bleach] = Tag::Liquid;
	lt[Item::Ink] = Tag::Liquid;
	lt[Item::Incense] = Tag::Perishable;
	lt[Item::Paper] = Tag::WaterDamage;
	lt[Item::Laxative] = Tag::Alternate;
	lt[Item::Tonic] = Tag::Alternate | Tag::Liquid;
	lt[Item::BoneMeal] = Tag::Perishable;
	lt[Item::FishMeal] = Tag::Perishable;
	lt[Item::Fertilizer] = Tag::Perishable;
	lt[Item::CoinMould] = Tag::Alternate;
	lt[Item::PrimitiveSpearHead] = Tag::Alternate;
	lt[Item::KnifeHead] = Tag::Alternate;
	lt[Item::SickleHead] = Tag::Alternate;
	lt[Item::AwlHead] = Tag::Alternate;
	lt[Item::AdzeHead] = Tag::Alternate;
	lt[Item::MalletHead] = Tag::Alternate;
	lt[Item::ScalpelHead] = Tag::Alternate;
	lt[Item::HammerHead] = Tag::Alternate;
	lt[Item::ChiselHead] = Tag::Alternate;
	lt[Item::TrowelHead] = Tag::Alternate;
	lt[Item::CleaverHead] = Tag::Alternate;
	lt[Item::MacheteHead] = Tag::Alternate;
	lt[Item::SwordHead] = Tag::Alternate;
	lt[Item::HandaxeHead] = Tag::Alternate;
	lt[Item::PermanentKnifeHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentSickleHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentAwlHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentAdzeHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentMalletHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentScalpelHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentHammerHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentChiselHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentTrowelHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentCleaverHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentMacheteHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentSwordHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PermanentHandaxeHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PrimitiveSpearHead] = Tag::Alternate;
	lt[Item::ScytheHead] = Tag::Alternate;
	lt[Item::PermanentScytheHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::ArdHead] = Tag::Alternate;
	lt[Item::PermanentArdHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::HeavySawHead] = Tag::Alternate;
	lt[Item::PermanentHeavySawHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::SawHead] = Tag::Alternate;
	lt[Item::PermanentSawHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::ShovelHead] = Tag::Alternate;
	lt[Item::PermanentShovelHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::AxeHead] = Tag::Alternate;
	lt[Item::PermanentAxeHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PickaxeHead] = Tag::Alternate;
	lt[Item::PermanentPickaxeHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::GreatswordHead] = Tag::Alternate;
	lt[Item::PermanentGreatswordHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::GreataxeHead] = Tag::Alternate;
	lt[Item::PermanentGreataxeHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::HalberdHead] = Tag::Alternate;
	lt[Item::PermanentHalberdHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::PikeHead] = Tag::Alternate;
	lt[Item::PermanentPikeHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::SpearHead] = Tag::Alternate;
	lt[Item::PermanentSpearHeadMould] = Tag::Alternate | Tag::Mould;
	lt[Item::Cloth] = Tag::WaterDamage;
	lt[Item::DyedCloth] = Tag::WaterDamage;
	lt[Item::Tribalwear] = Tag::Wearable;
	lt[Item::BasicClothes] = Tag::Wearable;
	lt[Item::FormalClothes] = Tag::VariableAmountsRequired | Tag::Wearable;
	lt[Item::FancyClothes] = Tag::VariableAmountsRequired | Tag::Wearable;
	lt[Item::GoldCrown] = Tag::Wearable;
	lt[Item::RoyalCrown] = Tag::Wearable;
	lt[Item::Necklace] = Tag::Wearable;
	lt[Item::Ring] = Tag::Alternate | Tag::Wearable;
	lt[Item::Earring] = Tag::Alternate | Tag::Wearable;
	lt[Item::Gambeson] = Tag::Wearable;
	lt[Item::DrawPlate] = Tag::Mould;
	lt[Item::Chainmail] = Tag::Wearable;
	lt[Item::Helmet] = Tag::Alternate | Tag::Wearable;
	lt[Item::Breastplate] = Tag::Alternate | Tag::Wearable;
	lt[Item::Guards] = Tag::Alternate | Tag::Wearable;
	lt[Item::Bracers] = Tag::Alternate | Tag::Wearable;
	lt[Item::Gloves] = Tag::Wearable;
	lt[Item::Apron] = Tag::Wearable;
	lt[Item::Sandals] = Tag::Wearable;
	lt[Item::Boots] = Tag::Wearable;
	lt[Item::Cape] = Tag::Wearable;
	lt[Item::Javelin] = Tag::Alternate;
	lt[Item::Torch] = Tag::WaterDamage;
	lt[Item::CandleMould] = Tag::Alternate;
	lt[Item::Candle] = Tag::Alternate | Tag::Wearable | Tag::WaterDamage;
	lt[Item::OilLamp] = Tag::Alternate | Tag::WaterDamage;
	lt[Item::Jar] = Tag::Container;
	lt[Item::Pot] = Tag::Container;
	lt[Item::Keg] = Tag::Container;
	lt[Item::Bottle] = Tag::Container;
	lt[Item::Kettle] = Tag::Container;
	lt[Item::Waterskin] = Tag::Container;
	lt[Item::Satchel] = Tag::Container;
	lt[Item::LargeSatchel] = Tag::Container;
	lt[Item::Bucket] = Tag::Container;
	lt[Item::Basket] = Tag::Container;
	return lt;
}();

} // namespace item

inline bool has_tag(Item item, item::Tag tag)
{
		return has_tag(item::TAGS[item], tag);
}
