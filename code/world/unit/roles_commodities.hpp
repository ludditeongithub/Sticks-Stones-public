#include "core/tables.hpp"
#include "world/unit/enum.hpp"
#include <variant>
#include <vector>
#include <world/item/enum.hpp>
#include <world/progression/enum.hpp>
#include <core/combo_enum.hpp>

using Commodity = ConcatEnum<Item, Buildable, Knowledge, Order, Ritual>;

template<typename... Cs>
constexpr auto mkv(Cs... cs) -> std::array<Commodity::underlying, sizeof...(Cs)> {
    return { Commodity::cast(cs)... };
}


// important: must be initialized in enum order!
inline constexpr RaggedLookupTable<Role, Commodity::underlying, 50000, Commodity::MAX>
    rolesToCommodities = []
{
	using u = Commodity::underlying;
	using enum Role;

	RaggedLookupTable<Role, u, 50000, Commodity::MAX> lt{};

	lt.set(Performer, mkv(Ritual::Song));
	lt.set(Bard, mkv(Ritual::Song, Ritual::InstrumentalSong));
	lt.set(Sculptor,
	       mkv(Item::SmallSculpture, Buildable::MediumSculpture, Buildable::LargeSculpture));
	lt.set(Goldsmith, mkv(Item::Ring, Item::Earring, Item::Necklace, Item::Bracelet));
	lt.set(Poet, mkv(Ritual::Poem));
	lt.set(StoneCarver, mkv(Item::SmallCarving, Buildable::LargeCarving));
	lt.set(Actor, mkv(Ritual::Play));
	lt.set(Playwright, mkv(Item::PlayScript));
	lt.set(Musician, mkv(Ritual::InstrumentalSong));
	lt.set(Decorator, mkv(Item::SmallPaintedCarving, Item::SmallPaintedSculpture,
			      Buildable::MediumPaintedSculpture, Buildable::LargePaintedCarving));
	lt.set(Painter, mkv(Item::PaperPainting, Item::CanvasPainting));
	lt.set(WoodCarver, mkv(Item::SmallCarving, Buildable::LargeCarving, Buildable::WallCarving));
	lt.set(Storyteller, mkv(Ritual::Story));
	lt.set(GemCarver, mkv(Item::CutGem, Item::CutGreaterGem, Item::GemSeal));
	lt.set(Potter, mkv(Item::Pot));
	lt.set(GlassArtist, mkv(Item::PaintedGlass));
	lt.set(Writer, mkv(Item::Novel, Item::ShortStory, Item::Pamphlet));
	lt.set(Ornamenter, mkv(Item::Earring, Item::Ring, Item::Necklace, Item::Bracelet));
	lt.set(ClayWorker,
	       mkv(Item::Pot, Item::Jar, Item::BrickMould, Item::PikeHeadMould, Item::PikeHead, Item::HalberdHeadMould, Item::HalberdHead,
		   Item::GreataxeHeadMould, Item::GreataxeHead, Item::GreatswordHeadMould,
		   Item::SpearHeadMould, Item::PickaxeHeadMould, Item::AxeHeadMould,
		   Item::ShovelHeadMould, Item::SawHeadMould, Item::ArdHeadMould,
		   Item::ScytheHeadMould, Item::HandaxeHeadMould, Item::SwordHeadMould,
		   Item::MacheteHeadMould, Item::CleaverHeadMould, Item::TrowelHeadMould,
		   Item::ChiselHeadMould, Item::HammerHeadMould, Item::ScalpelHeadMould,
		   Item::MalletHeadMould, Item::AdzeHeadMould, Item::AwlHeadMould,
		   Item::SickleHeadMould, Item::KnifeHeadMould));
	lt.set(Prince, mkv(Ritual::LeaderSpeech));
	lt.set(Philosopher, mkv(Ritual::PublicTeaching, Ritual::Debate, Knowledge::Academic));
	lt.set(AdvisorKnowledge, mkv(Ritual::PublicTeaching, Ritual::Debate, Ritual::KnowledgeBoost, Item::Book, Knowledge::Academic, Knowledge::Technology));
	lt.set(Emperor, mkv(Ritual::LeaderSpeech, Ritual::Decree));
	lt.set(Moneyer, mkv(Item::Coins, Ritual::MinterBoost));
	lt.set(AdvisorStructures, mkv(Ritual::BlueprintOrder, Ritual::MonumentBlueprintOrder));
	lt.set(Architect, mkv(Ritual::BlueprintOrder, Ritual::BuilderBoost));
	lt.set(King, mkv(Ritual::Decree, Ritual::LeaderSpeech));
	lt.set(AdvisorFarming, mkv(Ritual::AgricultureDecree, Order::Administrative));
	// TODO: continue from spreadsheet
	
	return lt;
}();
