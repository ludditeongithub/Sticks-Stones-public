#include "items.hpp"

struct UnitData
{
	std::vector<Item> equipment;
	std::vector<std::vector<Item>> inventories;
	std::vector<std::vector<int>> amounts;
	std::vector<int> work_left;

	uint16_t size() const { return work_left.size(); }

	void resize(uint16_t n)
	{
		inventories.resize(n);
		amounts.resize(n);
		work_left.resize(n, 0);
	}
};

void produce_items(std::vector<Item> &queue, std::vector<int> &amount, UnitData &units)
{
	for (uint16_t q = 0; q < queue.size(); ++q)
	{
		Item item = queue[q];
		if (item == Item::EMPTY || amount[q] == 0)
			continue;

		Recipe recipe = products[static_cast<int>(item)];

		for (uint16_t i = 0; i < units.size(); ++i)
		{
			if (units.work_left[i] != 0)
				continue;

			auto &inventory = units.inventories[i];
			auto &inv_amounts = units.amounts[i];

			std::vector<std::pair<int, int>> product_ingredients(
			    recipe.ingredients.size(), {-1, 0});
			bool missing_ingredients = false;

			for (uint16_t j = 0; j < recipe.ingredients.size(); ++j)
			{
				Item ingredient = recipe.ingredients[j];
				if (ingredient == Item::EMPTY)
					continue;

				int required_amount = recipe.amounts[j];
				int slot_type = recipe.replaceable[j];

				bool found = false;

				if (slot_type != 0)
				{ // not optional
					for (uint16_t k = 0; k < inventory.size(); ++k)
					{
						if (inventory[k] == ingredient &&
						    inv_amounts[k] >= required_amount)
						{
							product_ingredients[j] = {
							    static_cast<int>(k), required_amount};
							found = true;

							// skip other replaceables with same slot
							// type
							while (j + 1 < recipe.replaceable.size() &&
							       recipe.replaceable[j + 1] ==
								   slot_type)
								++j;

							break;
						}
					}

					if (!found)
					{
						// missing mandatory ingredient
						missing_ingredients = true;
						break;
					}
				}

				// If optional and not found — we just skip
			}

			if (missing_ingredients)
			{
				// Future: search surroundings, idle, etc.
				continue;
			}

			// All ingredients found — deduct from inventory
			for (const auto &[index, amt] : product_ingredients)
			{
				if (index >= 0)
				{
					inv_amounts[index] -= amt;
					// Optional: remove item if amount is now 0
					if (inv_amounts[index] == 0)
					{
						inventory.erase(inventory.begin() + index);
						inv_amounts.erase(inv_amounts.begin() + index);
					}
				}
			}

			units.work_left[i] = recipe.work_time;
		}
	}
}

enum EquipmentTag : uint8_t
{
	Tool,
	Weapon,
	Clothes,
	Armor,
	ForAnimals,
};

enum NumItemTraits
{
	AmtMadeOf, // creates array item_type
	Size,	   // ltf
	Weight,	   // ltf
	Beauty,	   // ltf
};

enum class PlaceableItemTraits
{
	SupportsRoof, // links to int, higher int means heavier roof, 0 for none
	Floor,
	Transport,
	Holds,		 // links to array item_type
	SecondDimension, // links to int which is its length
	Durability,	 // ltf
};

/* ITEM TRAIT SETS */

// for inventory management, units have array storing ints which map to the index of the enum
// classes, and then the same index of a second array is the index of the item within that enum
// class

enum class Surface
{

};

enum class Ingredients
{

};

enum class BaseMaterials
{

};

enum class CraftingItems
{

};

enum class Substances
{
	Bone,
	Wood,
	Stone,
	Leather,
	Cloth,
	Linen,
	Glass,
	Clay,
	Cob,
	Copper,
	Bronze,
	Iron,
	Steel,
	Silver,
	Gold,
	LesserGem,
	GreaterGem,
	Papyrus,
	Parchment,
};

enum class HealthItems
{

};

enum class Weapons
{

};

enum class Clothes
{

};

enum class Accessories
{

};

enum class Armor
{

};

enum class Ammo
{

};

enum class OtherEquipment
{

};

enum class AnimalTraits
{ // f
	GrowthRate,
	FullyGrown,
	Produces, // 0.0 if nothing
	Consumes,
	ConsumptionAmount,
	MoveSpeed,
	Mountable,
};

enum class SurfaceTraits
{ // f
	Weight,
	Size,
};

enum class EarthMaterialTraits
{
	StoneWaste
};

enum class IngredientTraits
{		 // i
	Quality, // cheap = 0, average = 1, expensive = 2, delicacy = 3
	Filling,
	Type,  // food = 0, drink = 1, oil = 2
	Taste, // savory = 0, sweet = 1, sour = 2, bitter = 3, spicy = 4
	Expiration,
};

enum class SubstanceTraits
{
	BeautyMultiplier,
	DurabilityMultiplier,
};

enum class BaseMaterialTraits
{ // i
	Durability,
	Substance,
};

enum class CraftingMaterialTraits
{
};

enum class HealthItemTraits
{		 // i
	Healing, // negative for poisons
	Curing,	 // diseases/symptoms it cures
	PainRelief,
	Humor, // 0 = Phlegm, 1 = Yellow Bile, 2 = BB, 3 = Blood
};

enum class WeaponTraits
{ // f
	Damage,
	SwingSpeed,
	Range,
	Pierce,
	AmmoRequired, // 0 if nothing
	ShieldBreaker,
};

enum class ToolTraits
{ // f
	// list of harvestable
	// list of producable
	// list of equipable by
	Durability,
};

enum class ArmorTraits
{
	Protection,
	Durability,
	Covers,
};

enum class ClothesTraits
{ // f
	Durability,
	Beauty,
};

enum class BuildingPieceTraits
{ // f
	Durability,
	Beauty,
	ModularValue,
	Type, // 0 if floor, 1 if wall, 2 if roof, changes modularvalue to movespeed,
	      // holdingstrength, weight respectively
};

enum class TransportTraits
{ // f
	Length,
	Width,
	MovementSpeed,
	Capacity,
	Water,
	WeightLimit,
};

enum class ContainerTraits
{ // i
	// list of objects it can hold
	Produces, // whether it produces an object, or just stores
	Capacity,
};

enum class StationTraits
{ // f
	Size,
	// list of activities that can be done here
};

enum class SiegeTraits
{ // i
	CrewAmount,
	Durability,
	Damage,
	Range,
};

/* UNIT TRAITS */
enum unit_traits
{
	// linked arrays are small int arrays
	IsAdult,
	CanCraft,	     // linked to array product_type
	ProducesIntangibles, // linked to array_intangible_type
	CanGather,	     // linked to array block_type
	CanBuff,	     // linked to array unit_type
	CanTrain,	     // linked to array unit_type
	HasAbilities,	     // linked to array ability_type
	CanMount,	     // linked to array animal_type
		  //  array equipment_type
};

/* ITEMS */
