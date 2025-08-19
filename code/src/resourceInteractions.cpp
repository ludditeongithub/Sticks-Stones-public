#include "traitdata.hpp"
#include "actions.hpp"


enum class Classes {
	Artist, Resource, Producer, Researcher, Support, Trainee, Melee, Ranged, Leader
};

enum class Subclasses {
	Self, Performer, Recipe, Artifact, Jeweller, Seal, ClayItem, String, Books, Monarch, Advisor, Miner, Hauler, MilitaryLeader, Engineer, Landowner, Charcoal, Food, LeatherArmor, Preserver, Stoneworker, Leather, TransportItem, Dies, Glass, Coin, Boat, Bow, Liquid, Smith, Fletcher, Brick, Lighting, Smelter, Textiles, Paper, Assembly, Builder, Academic, Baker, Butcher, Foreign, Researcher, Surveyor, Honey, Crops, Horses, Flour, Fish, Healer, Trader, Order, Plower, Letters, Children
};

struct Human {
	// Inventory
	Clothes clothes;
	// Unit Types
	bool resource = false;
	bool producer = false;
	bool artist = false;
	bool researcher = false;
	bool soldier = false;
	bool leader = false;
	std::vector<Subclasses> subclasses;
	std::optional<std::vector<Tools>> tools;
	std::optional<std::vector<AnimalProducts>> animalProducts;
	std::optional<std::vector<EarthMaterials>> earthMaterials;
	std::optional<std::vector<BaseMaterials>> baseMaterials;
	std::optional<std::vector<Ingredients>> ingredients;
	std::optional<std::vector<CraftingItems>> craftingItems;
	std::optional<std::vector<HealthItems>> healthItems;
	std::optional<std::vector<Armor>> armor;
	if (resource) {
		if (!tools) tools.emplace;
		if (!baseMaterials) baseMaterials.emplace;
	}

	}
	Weapon weapon;
};

// MAIN CLASSES

struct Resource : Human {

};

struct Producer : Human {
	// Inventory

};

struct Artist : Human {
	// Inventory
};

struct Researcher : Human {

};

struct Soldier : Human {

};

struct Leader : Human {
	std::vector<Abilities> abilities;
}


enum class Performers {
    Bard, Poet, Actor, Musician, Storyteller
};

enum class Performances {
	VocalSong, InstrumentalSong, Poem, Play, Story
};

enum class ArtRecipes {
	VocalSong, InstrumentalSong, Poem, Play, Story
};

struct Performer {
    const Performers type;
	const Actions action = Perform;
	const Performances performance;
	const ArtRecipes recipe;
	std::vector<Tools> tools;
    std::vector<Tools> singleTools; // one of these is mandatory
    std::vector<Tools> optionalTools;
	std::vector<CraftingItems> craftingItems;
	std::vector<CraftingItems> singleCraftingItems;
    std::vector<CraftingItems> optionalCraftingItems;

    Performer(Performers performerType) : type(performerType) {
        // Conditional setup based on performer type
        if (type == Performers::Bard) {
            optionalTools.push_back(Tools::Drum);
            optionalTools.push_back(Tools::Lyre);
			performance = Performances::VocalSong;
        }
        if (type == Performers::Poet) {
            optionalTools.push_back(Tools::QuillPen);
            optionalTools.push_back(Tools::ReedPen);
            optionalCraftingItems.push_back(CraftingItems::Ink);
            optionalCraftingItems.push_back(CraftingItems::Papyrus);
            optionalCraftingItems.push_back(CraftingItems::Parchment);
			performance = Performances::Poem;
        }
        if (type == Performers::Musician) {
            singleTools.push_back(Tools::Drum);
            singleTools.push_back(Tools::Lyre);
            singleTools.push_back(Tools::Lur);
            singleTools.push_back(Tools::PanFlute);
			optionalCraftingItems.push_back(CraftingItems::Ink);
            optionalCraftingItems.push_back(CraftingItems::Papyrus);
            optionalCraftingItems.push_back(CraftingItems::Parchment);
			performance = Performances::InstrumentalSong;
        }
		if (type == Performers::Storyteller) {
			performance = Performances::Story;
		}
		if (type == Performers::Actor) {
			performance = Performances::Play;
		}
    }
};



std::vector<Human> humans;
// HUMAN GAME LOOP
Human pawn = humans[i];
bool active[] = new bool [humans.size()];
// 1. Select Prioritized Action
// 1A. Check if Prioritized Action is Legal for Human
// 1B. If not, select next Prioritized Action
// 2. If no Prioritized Actions, then Select Default Action
for (int i = 0; i < pawn.subclasses.size(); i++) {
	Subclass s = pawn.subclasses[i];
	// make sure pawn required tools are satisfied
	bool requiredTools = false;
	for (int t = 0; t < s.requiredTools.size(); t++) {
		    bool toolFound = false;
			for (int a = 0; a < pawn.tools.size(); a++) {
				if (pawn.tools[a] == s.requiredTools[t]) {
					toolFound == true;
					break;
				}
			}
			if (!toolFound) {
				requiredTools = false;
				break;
			}
		}
	if (!requiredTools)	continue; // skip action
		// make sure tools that pawn requires at least one of a set of are satisfied
	bool requiredSingleTools = false;
		for (int t = 0; t < s.singleTools.size(); t++) {
			for (int a = 0; a < pawn.tools.size(); a++) {
				if (pawn.tools[a] == s.singleTools[t]) {
					requiredSingleTools = true;
					break;
				}
			}
			if (requiredSingleTools) break;
		}
		if (!requiredSingleTools) continue;

	bool requiredCraftingItems = false;
	for (int t = 0; t < s.requiredCraftingItems.size(); t++) {
		    bool itemFound = false;
			for (int a = 0; a < pawn.craftingItems.size(); a++) {
				if (pawn.craftingItems[a] == s.requiredCraftingItems[t]) {
					itemFound == true;
					break;
				}
			}
			if (!itemFound) {
				requiredcraftingItems = false;
				break;
			}
		}
	if (!requiredCraftingItems)	continue; // skip action

		bool requiredSingleCraftingItems = false;
		for (int t = 0; t < s.singleCraftingItems.size(); t++) {
			for (int a = 0; a < pawn.craftingItems.size(); a++) {
				if (pawn.tools[a] == s.craftingItems[t]) {
					requiredSingleCraftingItems = true;
					break;
				}
			}
			if (requiredSingleCraftingItems) break;
		}
		if (!requiredSingleCraftingItems) continue;

	// all requirements successful, start performing action
}
// 2A. Check if Default Action is Legal for Human
// 2B. If not, select next Default Action
// 3.  Go to location of Action
// 4. Do Action
