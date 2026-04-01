#pragma once
#include "core/tables.hpp"
#include "world/unit/enum.hpp"
#include <variant>
#include <vector>
#include <world/item/enum.hpp>
#include <world/progression/enum.hpp>
#include <core/combo_enum.hpp>

using Commodity = ConcatEnum<Item, Buildable, Knowledge, Order, Ritual>;

constexpr uint16_t ROLE_COMMODITY_JOB_AMOUNT = 4000;

template<typename... Cs>
constexpr auto mkv_commodity(Cs... cs) -> std::array<Commodity::underlying, sizeof...(Cs)> {
    return { Commodity::cast(cs)... };
}

// important: must be initialized in enum order!
inline constexpr RaggedLookupTable<Role, Commodity::underlying, ROLE_COMMODITY_JOB_AMOUNT,
				   Commodity::MAX>
    rolesToCommodities = []
{
	using u = Commodity::underlying;
	using enum Role;

	RaggedLookupTable<Role, u, ROLE_COMMODITY_JOB_AMOUNT, Commodity::MAX> lt{};

	lt.set(Performer, mkv_commodity(Ritual::Song));
	lt.set(Bard, mkv_commodity(Ritual::Song, Ritual::InstrumentalSong));
	lt.set(Sculptor,
	       mkv_commodity(Item::SmallSculpture, Buildable::MediumSculpture, Buildable::LargeSculpture));
	lt.set(Goldsmith, mkv_commodity(Item::Ring, Item::Earring, Item::Necklace, Item::Bracelet));
	lt.set(Poet, mkv_commodity(Ritual::Poem));
	lt.set(StoneCarver, mkv_commodity(Item::SmallCarving, Buildable::LargeCarving));
	lt.set(Actor, mkv_commodity(Ritual::Play));
	lt.set(Playwright, mkv_commodity(Item::PlayScript));
	lt.set(Musician, mkv_commodity(Ritual::InstrumentalSong));
	lt.set(Decorator, mkv_commodity(Item::SmallPaintedCarving, Item::SmallPaintedSculpture,
			      Buildable::MediumPaintedSculpture, Buildable::LargePaintedCarving));
	lt.set(Painter, mkv_commodity(Item::PaperPainting, Item::CanvasPainting));
	lt.set(WoodCarver, mkv_commodity(Item::SmallCarving, Buildable::LargeCarving, Buildable::WallCarving));
	lt.set(Storyteller, mkv_commodity(Ritual::Story));
	lt.set(GemCarver, mkv_commodity(Item::CutGem, Item::CutGreaterGem, Item::GemSeal));
	lt.set(Potter, mkv_commodity(Item::Pot));
	lt.set(GlassArtist, mkv_commodity(Item::PaintedGlass));
	lt.set(Writer, mkv_commodity(Item::Novel, Item::ShortStory, Item::Pamphlet));
	lt.set(Ornamenter, mkv_commodity(Item::Earring, Item::Ring, Item::Necklace, Item::Bracelet));
	lt.set(ClayWorker,
	       mkv_commodity(Item::Pot, Item::Jar, Item::BrickMould, Item::PikeHeadMould, Item::PikeHead, Item::HalberdHeadMould, Item::HalberdHead,
		   Item::GreataxeHeadMould, Item::GreataxeHead, Item::GreatswordHeadMould,
		   Item::SpearHeadMould, Item::PickaxeHeadMould, Item::AxeHeadMould,
		   Item::ShovelHeadMould, Item::SawHeadMould, Item::ArdHeadMould,
		   Item::ScytheHeadMould, Item::HandaxeHeadMould, Item::SwordHeadMould,
		   Item::MacheteHeadMould, Item::CleaverHeadMould, Item::TrowelHeadMould,
		   Item::ChiselHeadMould, Item::HammerHeadMould, Item::ScalpelHeadMould,
		   Item::MalletHeadMould, Item::AdzeHeadMould, Item::AwlHeadMould,
		   Item::SickleHeadMould, Item::KnifeHeadMould));
	lt.set(Prince, mkv_commodity(Ritual::LeaderSpeech));
	lt.set(Philosopher, mkv_commodity(Ritual::PublicTeaching, Ritual::Debate, Knowledge::Academic));
	lt.set(AdvisorKnowledge, mkv_commodity(Ritual::PublicTeaching, Ritual::Debate, Ritual::KnowledgeBoost, Item::Book, Knowledge::Academic, Knowledge::Technology));
	lt.set(Emperor, mkv_commodity(Ritual::LeaderSpeech, Ritual::Decree));
	lt.set(Moneyer, mkv_commodity(Item::Coins, Ritual::MinterBoost));
	lt.set(AdvisorStructures, mkv_commodity(Ritual::BlueprintOrder, Ritual::MonumentBlueprintOrder));
	lt.set(Architect, mkv_commodity(Ritual::BlueprintOrder, Ritual::BuilderBoost));
	lt.set(King, mkv_commodity(Ritual::Decree, Ritual::LeaderSpeech));
	lt.set(AdvisorFarming, mkv_commodity(Ritual::AgricultureDecree, Order::Administrative));
	// TODO: continue from spreadsheet
	//	lt.set(AdvisorTrade, mkv_commodity(Ritual::TradeDecree, ));
	
	return lt;
}();


