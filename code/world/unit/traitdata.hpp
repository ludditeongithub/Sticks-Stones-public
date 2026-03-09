#include "items.hpp"

struct UnitData {
    std::vector<Item> equipment;
    std::vector<std::vector<Item>> inventories;
    std::vector<std::vector<int>> amounts;
    std::vector<int> workLeft;

    uint16_t size() const { return workLeft.size(); }

    void resize(uint16_t n) {
        inventories.resize(n);
        amounts.resize(n);
        workLeft.resize(n, 0);
    }
};


void produceItems(std::vector<Item>& queue, std::vector<int>& amount, UnitData& units) {
    for (uint16_t q = 0; q < queue.size(); ++q) {
        Item item = queue[q];
        if (item == Item::EMPTY || amount[q] == 0) continue;

        Recipe recipe = products[static_cast<int>(item)];

        for (uint16_t i = 0; i < units.size(); ++i) {
            if (units.workLeft[i] != 0) continue;

            auto& inventory = units.inventories[i];
            auto& invAmounts = units.amounts[i];

            std::vector<std::pair<int, int>> productIngredients(recipe.ingredients.size(), {-1, 0});
            bool missingIngredients = false;

            for (uint16_t j = 0; j < recipe.ingredients.size(); ++j) {
                Item ingredient = recipe.ingredients[j];
                if (ingredient == Item::EMPTY) continue;

                int requiredAmount = recipe.amounts[j];
                int slotType = recipe.replaceable[j];

                bool found = false;

                if (slotType != 0) { // not optional
                    for (uint16_t k = 0; k < inventory.size(); ++k) {
                        if (inventory[k] == ingredient && invAmounts[k] >= requiredAmount) {
                            productIngredients[j] = {static_cast<int>(k), requiredAmount};
                            found = true;

                            // skip other replaceables with same slot type
                            while (j + 1 < recipe.replaceable.size() && recipe.replaceable[j + 1] == slotType)
                                ++j;

                            break;
                        }
                    }

                    if (!found) {
                        // missing mandatory ingredient
                        missingIngredients = true;
                        break;
                    }
                }

                // If optional and not found — we just skip
            }

            if (missingIngredients) {
                // Future: search surroundings, idle, etc.
                continue;
            }

            // All ingredients found — deduct from inventory
            for (const auto& [index, amt] : productIngredients) {
                if (index >= 0) {
                    invAmounts[index] -= amt;
                    // Optional: remove item if amount is now 0
                    if (invAmounts[index] == 0) {
                        inventory.erase(inventory.begin() + index);
                        invAmounts.erase(invAmounts.begin() + index);
                    }
                }
            }

            units.workLeft[i] = recipe.workTime;
        }
    }
}


enum EquipmentTag : uint8_t {
    Tool,
    Weapon,
    Clothes,
    Armor,
    ForAnimals,
};

enum NumItemTraits {
    AmtMadeOf, //creates array itemType
    Size, //ltf
    Weight, //ltf
    Beauty, //ltf
};

enum class PlaceableItemTraits {
    SupportsRoof, //links to int, higher int means heavier roof, 0 for none
    Floor,
    Transport,
    Holds,  //links to array itemType
    SecondDimension, //links to int which is its length
    Durability, //ltf
};


/* ITEM TRAIT SETS */

// for inventory management, units have array storing ints which map to the index of the enum classes, and then the same index of a second array is the index of the item within that enum class

enum class Surface {

};


enum class Ingredients {

};

enum class BaseMaterials {

};

enum class CraftingItems {

};

enum class Substances {
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

enum class HealthItems {

};

enum class Weapons {

};

enum class Clothes {

};

enum class Accessories {

};

enum class Armor {

};

enum class Ammo {

};

enum class OtherEquipment {

};

enum class AnimalTraits { //f
   GrowthRate,
   FullyGrown,
   Produces, //0.0 if nothing
   Consumes,
   ConsumptionAmount,
   MoveSpeed,
   Mountable,
};

enum class SurfaceTraits { //f
    Weight,
    Size,
};

enum class EarthMaterialTraits {
    StoneWaste
};

enum class IngredientTraits { //i
    Quality, // cheap = 0, average = 1, expensive = 2, delicacy = 3
    Filling,
    Type, // food = 0, drink = 1, oil = 2
    Taste, // savory = 0, sweet = 1, sour = 2, bitter = 3, spicy = 4
    Expiration,
};

enum class SubstanceTraits {
    BeautyMultiplier,
    DurabilityMultiplier,
};

enum class BaseMaterialTraits { //i
    Durability,
    Substance,
};

enum class CraftingMaterialTraits {};

enum class HealthItemTraits { //i
    Healing, // negative for poisons
    Curing, // diseases/symptoms it cures
    PainRelief,
    Humor, // 0 = Phlegm, 1 = Yellow Bile, 2 = BB, 3 = Blood
};

enum class WeaponTraits { //f
    Damage,
    SwingSpeed,
    Range,
    Pierce,
    AmmoRequired, //0 if nothing
    ShieldBreaker,
};

enum class ToolTraits { //f
    //list of harvestable
    //list of producable
    //list of equipable by
    Durability,
};

enum class ArmorTraits {
    Protection,
    Durability,
    Covers,
};

enum class ClothesTraits { //f
    Durability,
    Beauty,
};

enum class BuildingPieceTraits { //f
    Durability,
    Beauty,
    ModularValue,
    Type, //0 if floor, 1 if wall, 2 if roof, changes modularvalue to movespeed, holdingstrength, weight respectively
};

enum class TransportTraits { //f
    Length,
    Width,
    MovementSpeed,
    Capacity,
    Water,
    WeightLimit,
};

enum class ContainerTraits { //i
    //list of objects it can hold
    Produces, //whether it produces an object, or just stores
    Capacity,
};

enum class StationTraits { //f
    Size,
    //list of activities that can be done here
};

enum class SiegeTraits { //i
    CrewAmount,
    Durability,
    Damage,
    Range,
};

/* UNIT TRAITS */
enum unitTraits {
// linked arrays are small int arrays
    IsAdult,
    CanCraft,   //linked to array productType
    ProducesIntangibles, //linked to arrayIntangibleType
    CanGather,   //linked to array blockType
    CanBuff,      //linked to array unitType
    CanTrain,     //linked to array unitType
    HasAbilities, //linked to array abilityType
    CanMount,     //linked to array animalType
                  // array equipmentType
};

/* ITEMS */
