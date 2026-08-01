#ifndef GEAR_H_
#define GEAR_H_

#include <core/tables.hpp>
#include <core/data.hpp>
#include <world/item/data.hpp>
#include <vector>
#include <optional>
enum class BodyArea {
		Head, Shoulders, Arms, Chest, Belly, Thighs, Shins, Feet, MAX
};

// at base material, cloth for underlayers and bronze for armor,  and average quality.
struct ClothingData
{
	float toughness;
	float durability;
	float bulk;
	float weight;
	BulkLevel bulk_level;
	float min_temp;
	float max_temp;
	BitsetTable<BodyArea> covers;
};

// @codegen:begin specialization
enum class Wearable {
  PartTribalwear,
  Tribalwear,
  Robe,
  Tunic,
  Pants,
  Dress,
  Sandles,
  Boots,
  Scarf,
  Headwrap,
  Mitts,
  Gloves,
  Apron,
  Helmet,
  Bracers,
  Guards,
  Cape,
  HeavyShirt,
  HeavyPants,
  Gambeson,
  Chainmail,
  Breastplate,
  Plate,
  WoodCrown,
  GoldCrown,
  RoyalCrown,
  Necklace,
  MAX
};

inline constexpr LookupTable<Wearable, Health> healths = [] {
LookupTable<Wearable, Health> lt{};
  using enum Wearable;
return lt;
}();
inline constexpr LookupTable<Wearable, Quality> qualitys = [] {
LookupTable<Wearable, Quality> lt{};
  using enum Wearable;
return lt;
}();
inline constexpr LookupTable<Wearable, bool> equippeds = [] {
LookupTable<Wearable, bool> lt{};
  using enum Wearable;
return lt;
}();

struct WearableDatabase {
Database database;
  Array<Health> healths;
  Array<Quality> qualitys;
  Array<bool> equippeds;

// =========================
// CONSTRUCTOR
// =========================

WearableDatabase(Arena* arena, size_t size) {
database = Database(arena, size);
healths = arena_make_array<Health>(arena, database);
qualitys = arena_make_array<Quality>(arena, database);
equippeds = arena_make_array<bool>(arena, database);
}

// =========================
// GETTERS
// =========================

  inline Health& health(size_t index) {
return healths[index];
  }
  inline Quality& quality(size_t index) {
return qualitys[index];
  }
  inline bool& equipped(size_t index) {
return equippeds[index];
  }

// =========================
// SPAWN
// =========================

void spawn(Item item, bool newborn, Coord coord, Variant variant , Health health
, Quality quality
, bool equipped
)
{
size_t index = database.spawn(item, newborn, coord, variant, true);
  health(i) = health;
  quality(i) = quality;
  equipped(i) = equipped;
}

// =========================
// REMOVE
// =========================

  inline bool remove(size_t i)
  {
        database.remove(i);
  }

// =========================
  // MOVE
  // =========================

 inline bool attempt_move_entity(size_t index)
    {
        return database.attempt_move_entity(index);
    }

// =========================
// SERIALIZATION
// =========================

    template <class Archive>
    void save(Archive &archive) const
    {
      database.save(archive);
        health.save(archive);
        quality.save(archive);
        equipped.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        database.load(archive);
        health.load(archive);
        quality.load(archive);
        equipped.load(archive);
    }
  
// =========================
// TRANSFER
// =========================

inline bool transfer(size_t i, wearable::Database &old_db)
{
if (database.transfer(old_db.database)) {
    new_db.health[index] = old_db.health[i];
    new_db.quality[index] = old_db.quality[i];
    new_db.equipped[index] = old_db.equipped[i];
} else return false;
}

// =========================
// INVENTORY MANAGEMENT
// =========================

inline void pick_up(EntityID wearableID, Inventory& inventory) {
WearableEntity wearable = get_entity(index);
Item item = reflect_enum(wearable.specialization);
inventory.add_item(item);
remove_wearable(wearableID);
}

inline void drop(EntityID wearableID, Inventory& inventory) {
add_entity();
}
// @codegen:end specialization


struct AccesoryData
{
};

struct WeaponData
{
	int range;
	float damage;
	float speed;
	float durability;
	bool sharp;	     // whether it needs to be sharp, or if it is purely a smasher
	float pierce_or_smash; // pierce/smash value
};

constexpr float SLOW = 0.4;
constexpr float MEDIUM = 1.0;
constexpr float FAST = 1.6;

struct ToolData
{
	vector<std::pair<Actions, float>>
	    action_data; // last float takes speed from action data lookup table that says whether
			// tool is SLOW MEDIUM or FAST at that particular task, multiples that value
			// by time. Can override time instead of multiplying by making it a negative
	uint16_t durability; // how many times it can perform tasks before wearing out/breaking
	float bulk;
	float weight;
	BulkLevel bulk_level = BulkLevel::Solid;
	std::optional<uint16_t> sharpness;
};

struct VariableGearData
{
	Quality quality;
	Material material;
};

// only values other than MEDIUM are listed, MEDIUM is default and assummed if not found
void init_tool_data()
{
	// TODO: find actions for handaxe
	Handaxe
	{
		{
			{
			}
		}
	}
	Machete{{{Actions::Cut, FAST}, {Actions::FineChop, SLOW}, {Actions::Shear, SLOW}},
		1800,
		8.5,
		2.5,
		BulkLevel::Solid,
		250} Knife{{{Actions::FineChop, FAST}, {Actions::Butcher, SLOW}} 2000,
			   3.2,
			   0.8,
			   BulkLevel::Solid,
			   200} // TODO: balance, right now just worse than machete
	Cleaver{{}, 3500, 6.2, 1.2, BulkLevel::Solid, 120} Trowel{
	    {{Actions::Dig, SLOW}, {Actions::Weed, FAST}}, 2500, 5.4, 1.2, BulkLevel::Solid} Chisel{
	    {{Actions::Knapp, FAST}}, 480, 1.2, 3.4, BulkLevel::Solid} Hammer{
	    {{Actions::Build, FAST}, {Actions::Crush, FAST}},
	    2200,
	    7.2,
	    5.8,
	    BulkLevel::Solid} Scalpel{
	    {{Actions::Operate, FAST}, 4800, 1.1, 0.6, BulkLevel::Solid} Mallet{
		{{Actions::WoodCarve, SLOW}}, 1600, 4.2, 3.3} Sickle{{}, 8000, 4.2, 3.3} Adze{
		{}, 1800, 3.2, 2.1} Awl{{}, 1800, 3.2, 2.1} Graver{{}, 800, 1.2, 0.7} Pickaxe{
		{}, 50, 12.6, 8.8} Axe{{Actions::CanoeCarve, SLOW}, 480, 14.2, 9.2} Shovel{
		{Actions::Dig, FAST}, 2800, 24.8, 12.2} Saw{
		{Actions::CanoeCarve, FAST}, 250, 18.8, 5.2} // TODO: check ard facts
	    Ard{{Actions::Plow, SLOW}, 1400, 22.8, 25.8} HeavyPlow{
		{Actions::Plow, FAST}, 1000, 43.9, 75.8, BulkLevel::Single} Whip{Actions::Herd,
										 FAST},
	    4500,
	    1.0,
	    1.0,
	    BulkLevel::Soft}
	// TODO: allow fishing rod to catch speciality fish, research fishig methods, require string
	FishingRod{{Actions::Fish, SLOW}, 95, 16.2, 2.8} Staff{1800, 12.2, 7.8} DiggingStick{
	    {Actions::Dig, SLOW}, 320, 9.5, 3.0} Scythe{
	    {Actions::Harvest, FAST}, 4000, 16.2, 4.4} Blowpipe{{}, 6000, 3.1, 1.5} Shears{
	    {Actions::Shear, FAST}, 1800, 5.3, 4.5, .sharpness = 40} // TODO
	HandheldBellows Pestle{{}, 40000, 2.5, 2.5} Needle{
	    {}, 4, 0.04, 0.002, BulkLevel::Loose} Drum{{}, 200, 20.2, 14.6} Torch{
	    {},
	}

	bulk_and_weights[static_cast<int>(Item::SimpleLoom)] = {34.0f, 8.5f, BulkLevel::Single};
	bulk_and_weights[static_cast<int>(Item::Blowpipe)] = {0.5f, 1.0f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Container::Crucible) + static_cast<int>(Item::MAX)] = {
	    0.5f, 2.5f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Item::Whip)] = {1.8f, 0.5f, BulkLevel::Soft};
	bulk_and_weights[static_cast<int>(Item::HandheldBellows)] = {0.6f, 1.2f, BulkLevel::Soft};
}

void init_weapon_data()
{

	bulk_and_weights[static_cast<int>(Item::Shortbow)] = {15.5f, 0.8f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Item::Bow)] = {20.6f, 1.0f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Item::Crossbow)] = {25.8f, 2.5f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Item::Longbow)] = {28.9f, 1.5f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Item::Spear)] = {19.9f, 2.0f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Item::Axe)] = {17.0f, 2.5f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Item::Sword)] = {18.0f, 3.0f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Item::Greataxe)] = {28.2f, 7.5f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Item::Halberd)] = {24.3f, 5.0f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Item::Pike)] = {43.0f, 4.0f, BulkLevel::Single};
}

void init_container_data()
{
	bulk_and_weights[static_cast<int>(Container::Pot) + static_cast<int>(Item::MAX)] = {
	    5.7f, 2.0f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Container::LargePot) + static_cast<int>(Item::MAX)] = {
	    20.7f, 8.0f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Container::Kettle) + static_cast<int>(Item::MAX)] = {
	    3.8f, 2.5f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Container::Jar) + static_cast<int>(Item::MAX)] = {
	    0.8f, 1.0f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Container::Bucket) + static_cast<int>(Item::MAX)] = {
	    14.6f, 2.5f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Container::Basket) + static_cast<int>(Item::MAX)] = {
	    10.4f, 0.70f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Container::Satchel) + static_cast<int>(Item::MAX)] = {
	    0.6f, 0.30f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Container::Bottle) + static_cast<int>(Item::MAX)] = {
	    0.4f, 0.10f, BulkLevel::Solid};
	bulk_and_weights[static_cast<int>(Container::LargeSatchel) + static_cast<int>(Item::MAX)] = {
	    1.2f, 0.20f, BulkLevel::Solid};
}
#endif // GEAR_H_
