#ifndef ROLES_H_
#define ROLES_H_
#include "enum.hpp"
#include <world/action/enum.hpp>
#include <core/data.hpp>
#include <cstdint>
#include <limits>
#include <vector>
#include <variant>
#include <world/item/enum.hpp>
#include <world/buildable/enum.hpp>
#include <core/tables.hpp>

constexpr uint16_t MAX_ROLES_PER_TASK = 6;
constexpr uint16_t ACTION_TOOLS_AMOUNT = 100; // NOTE: likely wrong
constexpr uint16_t ACTION_MAX_REQUIREMENTS = 7; // NOTE: likely wrong

struct RoleData
{
	uint8_t cost;
	Time age;
	std::vector<std::vector<Role>> valid_prerequisite_role;
	std::vector<std::vector<Role>> requisites_of;
	std::vector<std::pair<Role, uint8_t>> reductions;
	std::vector<int> apprentice_time;
};

RoleData role_datas[static_cast<int>(Role::MAX)];

struct ActionRequirement
{
	std::variant<Buildable, Item> requirement;
	uint8_t index;
        uint8_t amount;
};

inline RaggedLookupTable<Action, ActionRequirement> action_to_tools = [] {
	RaggedLookupTable<Action, ActionRequirement> lt{};
	using enum Action;
	lt.set(Action::Pott, {
    {Buildable::Oven, 1},
    {Buildable::Furnace, 1},
    {Buildable::PottersWheel, 0},
    {Item::Scraper, -1},
    {Item::Stylus, -2}
});

lt.set(Action::Smelt, {
    {Buildable::Furnace, 0},
    {Item::Crucible, 1}
});

lt.set(Action::Smith, {
    {Buildable::Anvil, 0},
    {Item::Hammer, 1},
    {Item::Chisel, 2}
});

lt.set(Action::Perform, {
    {Item::Lyre, -1},
    {Item::Drum, -1},
    {Item::Lur, -1},
    {Item::PanFlute, -1}
});

lt.set(Action::Operate, {
    {Item::Scalpel, 0},
    {Item::Needle, 1}
});

lt.set(Action::Build, {
    {Item::Hammer, -1},
    {Item::Mallet, -1}
});

lt.set(Action::GlassMake, {
    {Item::HandheldBellows, 0},
    {Buildable::Bellows, 0},
    {Buildable::DoubleBellows, 0},
    {Buildable::RollingMachine, 1},
    {Buildable::Furnace, 2}
});

lt.set(Action::Burn, {
    {Item::Candle, 0},
    {Item::Flint, 1},
    {Item::Torch, 2}
});

lt.set(Action::WoodCarve, {
    {Item::Chisel, 0},
    {Item::Adze, 1},
    {Item::Knife, 2},
    {Item::Mallet, 0}
});

lt.set(Action::Weave, {
    {Item::HandheldLoom, 0},
    {Buildable::Loom, 1}
});

lt.set(Action::Cook, {
    {Item::Pot, 0},
    {Buildable::Oven, 1},
    {Buildable::Tabletop, 2}
});

lt.set(Action::Harvest, {
    {Item::Sickle, -1},
    {Item::Scythe, -1}
});

lt.set(Action::Milk, {
    {Item::Bucket, 0},
    {Item::Pot, 0},
    {Item::Jar, 0}
});

lt.set(Action::Trade, {
    {Item::Bucket, -1},
    {Item::Basket, -1},
    {Item::Jar, -1}
});

lt.set(Action::Mix, {
    {Item::Staff, 0},
    {Item::Stick, 0},
    {Item::Bucket, 1},
    {Item::ClayPot, 1},
    {Item::Pot, 1}
});

lt.set(Action::Churn, {
    {Item::Staff, 0},
    {Item::Stick, 0},
    {Item::Bucket, 1},
    {Item::ClayPot, 1},
    {Item::Pot, 1}
});

lt.set(Action::Boil, {
    {Buildable::PitFire, 0},
    {Buildable::Oven, 0},
    {Item::Bucket, 1},
    {Item::Pot, 1}
});

lt.set(Action::Spin, {
    {Item::Spindle, 0},
    {Item::Distaff, 0},
    {Buildable::Spinner, -1}
});

lt.set(Action::LeatherCraft, {
    {Item::Knife, 0},
    {Item::Awl, 1},
    {Item::Needle, 2}
});

lt.set(Action::CanoeCarve, {
    {Item::Saw, 0},
    {Item::Axe, 0},
    {Item::Adze, 1}
});

lt.set(Action::MudbrickSculpt, {
    {Item::Trowel, 1},
    {Item::BrickMould, -2}
});

lt.set(Action::BrickSculpt, {
    {Item::Trowel, 1},
    {Item::BrickMould, -2}
});

lt.set(Action::Mash, {
    {Item::Pestle, 1},
    {Buildable::Mill, 1}
});

lt.set(Action::StoneCarve, {
    {Item::Chisel, 0},
    {Item::Mallet, 1},
    {Item::Scraper, 2}
});

lt.set(Action::Sculpt, {
    {Item::Scraper, 0},
    {Item::Stylus, 1},
    {Item::MeasuringItems, -1}
});
	return lt;
	    }();

inline const RaggedLookupTable<Action, Role> action_to_roles = []
	    {		    
		    RaggedLookupTable<Action, Role> lt{};
  			using enum Action;   
		    lt.set(Action::Melee, {Role::MeleeSoldier, Role::SpearHunter});
		    lt.set(Action::Mine, {Role::StoneMiner, Role::CopperMiner, Role::IronMiner, Role::GoldMiner, Role::SilverMiner, Role::SaltMiner});
			lt.set(Action::Cut, {Role::Apothecary, Role::Planter});
			lt.set(Action::Chop, {Role::Woodcutter});
			lt.set(Action::FineChop, {Role::Cook, Role::Chef, Role::Apothecary});
			lt.set(Action::Dig, {Role::Planter, Role::Builder});
			lt.set(Action::Light, {Role::NONE});
			lt.set(Action::Butcher, {Role::Butcher});
			lt.set(Action::Paint, {Role::Painter});
			lt.set(Action::Sculpt, {Role::Sculptor, Role::ClayWorker, Role::Potter});
			lt.set(Action::Chisel, {Role::Stoneworker});
			lt.set(Action::Write, {Role::BooksAcademicAny, Role::BooksAcademicHistory, Role::BooksAcademicPhilosophy, Role::BooksAcademicMathematics, Role::BooksAcademicNatural, Role::Scribe, Role::AdvisorKnowledge, Role::AdvisorOrderAdministrative});
			   lt.set(Action::LowPott, {Role::ClayWorker});
			   lt.set(Action::Pott, {Role::Potter});
			   lt.set(Action::Pott, {Role::Potter});
			   lt.set(Action::Smelt, {Role::CopperSmelter, Role::BronzeSmelter, Role::IronSmelter, Role::SteelSmelter, Role::SilverSmelter, Role::GoldSmelter});
			   lt.set(Action::Smith, {Role::Coppersmith, Role::Bronzesmith, Role::Ironsmith,
				   Role::Steelsmith, Role::Silversmith, Role::Goldsmith});
			   lt.set(Action::Perform, {Role::Performer});
			   // TODO: alternate shitty operation tools
			   lt.set(Action::Operate, {Role::Surgeon});
			   lt.set(Action::Administer, {Role::Surgeon, Role::Herbalist, Role::Apothecary});
			   lt.set(Action::Build, {Role::ShelterBuilder, Role::Builder});
			   lt.set(Action::Mould, {Role::Chandler, Role::Potter});
                            lt.set(Action::Woodwork, {Role::Woodworker});
			    lt.set(Action::Stonework, {Role::Stoneworker});
	lt.set(Action::GlassMake, {Role::GlassMaker});
	lt.set(Action::Glasswork, {Role::Glassworker});
	lt.set(Action::Glasswork, {Role::Glassworker});
	lt.set(Action::Saw, {Role::Woodworker, Role::Woodcutter});
	lt.set(Action::Engrave, {Role::Engraver, Role::GemCarver, Role::WoodCarver});
	lt.set(Action::Burn, {Role::Firekeeper});
	// NOTE: figure out who can do fire
	lt.set(Action::Fire, {Role::CharcoalMaker, Role::Potter});
	lt.set(Action::Press, {Role::Planter});
	lt.set(Action::Carve, {Role::Carver});
	lt.set(Action::WoodCarve, {Role::WoodCarver});
	lt.set(Action::Weave, {Role::Weaver});
	lt.set(Action::BasketWeave, {Role::BasketWeaver});
	lt.set(Action::Bless, {Role::Priest});
	lt.set(Action::Cook, {Role::Cook});
	lt.set(Action::Craft, {Role::Crafter});
	lt.set(Action::Explore, {Role::Explorer});
	lt.set(Action::Negotiate, {Role::Negotiator});
	lt.set(Action::Plow, {Role::Plower});
	lt.set(Action::Plant, {Role::Planter});
	lt.set(Action::Weed, {Role::Planter});
	lt.set(Action::Harvest, {Role::Planter});
	lt.set(Action::Milk, {Role::Herder, Role::Shepherd});
	lt.set(Action::Shear, {Role::Herder, Role::Shepherd});
	lt.set(Action::Mill, {Role::GrainGrinder, Role::Miller});
	lt.set(Action::Fish, {Role::Fisherman});
	lt.set(Action::Herd, {Role::Herder, Role::Shepherd});
	lt.set(Action::Trade, {Role::Trader});
	lt.set(Action::Haul, {Role::Hauler});
	lt.set(Action::Bake, {Role::Baker});
	lt.set(Action::Treat, {Role::Dyer, Role::PaperMaker});
	lt.set(Action::Cur, {Role::Butcher, Role::Tanner});
	lt.set(Action::Tan, {Role::Tanner});
	lt.set(Action::Cast, {Role::Founder, Role::Silversmith, Role::Goldsmith});
	lt.set(Action::Mix, {Role::Mixer});
	lt.set(Action::Boil, {Role::Cook, Role::Firekeeper});
	lt.set(Action::Whittle, {Role::Woodworker, Role::Carver});
	lt.set(Action::Knapp, {Role::Knapper, Role::StoneWorker});
	lt.set(Action::Spin, {Role::Spinner});
	lt.set(Action::Grind, {Role::Apothecary});
	lt.set(Action::Preserve, {Role::Preserver});
	// NOTE: maybe change awl to optional
	lt.set(Action::LeatherCraft, {Role::Leathercrafter, Role::Cuirassier});
	lt.set(Action::Dip, {Role::Chandler});
	lt.set(Action::CandleMould, {Role::Chandler});
	lt.set(Action::Lay, {Role::Ropemaker});
	lt.set(Action::WoodCraft, {Role::Woodworker});
	lt.set(Action::WheelCraft, {Role::Wheelwright});
	lt.set(Action::CanoeCarve, {Role::CanoeCarver});
	lt.set(Action::BoatCraft, {Role::BoatBuilder, Role::Shipwright});
	lt.set(Action::SiegeCraft, {Role::SiegeEngineer});
	lt.set(Action::Engineer, {Role::Engineer});
	// NOTE: maybe change awl to optional
	lt.set(Action::BowCraft, {Role::Bowyer});
	lt.set(Action::MudbrickSculpt, {Role::MudbrickMaker});
	lt.set(Action::BrickSculpt, {Role::BrickMaker});
	lt.set(Action::Mash, {Role::Brewer});
	// TODO: make sure this works
	lt.set(Action::Brew, {Role::Brewer});
	lt.set(Action::OilMake, {Role::OilMaker});
	// to do roles
	lt.set(Action::SculptMould, {Role::Sculptor});
	lt.set(Action::Sew, {Role::Tailor});
	lt.set(Action::Cur, {Role::Butcher, Role::Tanner});
	lt.set(Action::CandleCast, {Role::Chandler});
	lt.set(Action::Mint, {Role::Minter});

	// NON PRODUCT/RESOURCE
	lt.set(Action::Tame, {Role::HorseBreeder, Role::Shepherd, Role::Herder});
		    return lt;
	    }();	    
#endif // ROLES_H_
