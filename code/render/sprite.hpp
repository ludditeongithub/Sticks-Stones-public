// Stores hot arrays of sprite data (positions, sizes, colors, texture IDs), handles batching logic
#pragma once
#include <world/item/enum.hpp>
#include <world/buildable/enum.hpp>
#include <world/animal/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/unit/enum.hpp>
#include <world/tile/enum.hpp>
#include <core/data.hpp>
#include <variant>
#include <ui/components/button.hpp>
#include <iostream>
#include <memory>

// TODO: right now this is only fitted for walk animations. need to make sure
// all the LOGIC is only fitted for walk animations, for now.

struct SpriteInfo
{
    uint8_t SIDE_LENGTH;
    uint8_t SIDE_HEIGHT;
    uint8_t FRONT_LENGTH;
    uint8_t FRONT_HEIGHT;

    uint8_t CHILD_SIDE_LENGTH;
    uint8_t CHILD_SIDE_HEIGHT;
    uint8_t CHILD_FRONT_LENGTH;
    uint8_t CHILD_FRONT_HEIGHT;

    uint8_t WALKING_SPRITE_LENGTH = 0;
    uint8_t RUNNING_SPRITE_LENGTH = 0;

    Frame WALK_SPRITE_FRAME_LENGTH{};
    Frame RUN_SPRITE_FRAME_LENGTH{};
    Frame ACT_SPRITE_FRAME_LENGTH{};

    constexpr SpriteInfo() = default;

    constexpr SpriteInfo(uint8_t SIDE_LENGTH, uint8_t SIDE_HEIGHT, uint8_t FRONT_LENGTH,
			 uint8_t FRONT_HEIGHT, uint8_t CHILD_SIDE_LENGTH, uint8_t CHILD_SIDE_HEIGHT,
			 uint8_t CHILD_FRONT_LENGTH,
			 uint8_t CHILD_FRONT_HEIGHT)
        : SIDE_LENGTH(SIDE_LENGTH),
          SIDE_HEIGHT(SIDE_HEIGHT),
          FRONT_LENGTH(FRONT_LENGTH),
          FRONT_HEIGHT(FRONT_HEIGHT),
          CHILD_SIDE_LENGTH(CHILD_SIDE_LENGTH),
          CHILD_SIDE_HEIGHT(CHILD_SIDE_HEIGHT),
          CHILD_FRONT_LENGTH(CHILD_FRONT_LENGTH),
          CHILD_FRONT_HEIGHT(CHILD_FRONT_HEIGHT)
    {}
};

inline constexpr LookupTable<Animal, SpriteInfo> animalSpriteInfos = []
{
    LookupTable<Animal, SpriteInfo> lt{};

    using enum Animal;

    lt[Pig]          = SpriteInfo(2,1,1,2,2,1,1,2);
    lt[Cow]          = SpriteInfo(3,2,1,3,3,2,2,2);
    lt[Chicken]      = SpriteInfo(1,1,1,1,1,1,1,1);
    lt[Duck]         = SpriteInfo(1,1,1,1,1,1,1,1);
    lt[Sheep]        = SpriteInfo(2,1,1,2,2,1,1,1);
    lt[Goat]         = SpriteInfo(2,1,1,2,2,1,1,1);
    lt[Horse]        = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Ox]           = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Donkey]       = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Camel]        = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[WaterBuffalo] = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Rabbit]       = SpriteInfo(1,1,1,1,1,1,1,1);
    lt[Antelope]     = SpriteInfo(3,2,1,2,2,2,1,2);
    lt[Deer]         = SpriteInfo(2,2,1,2,2,2,1,2);
    lt[Moose]        = SpriteInfo(4,3,2,3,3,2,2,3);
    lt[Capybara]     = SpriteInfo(2,1,1,2,2,1,1,1);
    lt[Turtle]       = SpriteInfo(1,1,1,1,1,1,1,1);
    lt[Elephant]     = SpriteInfo(5,3,2,3,4,3,2,3);
    lt[Bison]        = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Wolf]         = SpriteInfo(3,2,1,3,3,2,1,3);
    lt[Bear]         = SpriteInfo(3,2,1,3,2,2,1,2);
    lt[Caribou]      = SpriteInfo(3,2,1,2,2,2,1,2);

    return lt;
}();

constexpr uint8_t MAX_STAGES = 4;

struct StageInfo {
	SDL_Rect dimensions;
	uint8_t stages;
	 constexpr StageInfo() = default;	
	constexpr StageInfo(SDL_Rect dimensions, uint8_t stages)
	    : dimensions(dimensions), stages(stages)
	{
	}
};

inline constexpr BitsetTable<Plant> plantSpriteProgressiveStages = []
	{
		BitsetTable<Plant> t{};
		using enum Plant;
		t.set(Moss);
	};

inline constexpr BitsetTable<Plant> plantProduces = []
	{
		BitsetTable<Plant> t{};
		using enum Plant;
	};

inline constexpr LookupTable<Plant,std::array<StageInfo, MAX_STAGES>> plantSpriteDimensions = [] {
	LookupTable<Plant,std::array<StageInfo, MAX_STAGES>> lt{};
	using enum Plant;
	lt[Fern] = {{{{1,1}, 3}}};
	lt[Moss] = {{{{1,1}, 12}}};
	lt[Reed] = {{StageInfo({2,2}, 1)}};
	lt[Wheat] = {{StageInfo({1,2},4)}};
	lt[Oat] = {{StageInfo({1,1},3), StageInfo({1,2},2)}};
	lt[Rice] = {{StageInfo({1,1},5)}};
	lt[Bush] = {{StageInfo({1,1},4)}, StageInfo({2,2},3)};
	lt[Papyrus] = {{ }}; //TODO
	lt[PioneerTree] = {{ }}; //TODO
	lt[DeciduousTree] = {{StageInfo({1,1},1),StageInfo({1,2},1), StageInfo({3,4},1)}}; //TODO (separate from regular 'tree', possibly, as those are unbarren fruit trees. make sure they are the same as the unbarren fruit trees)
	lt[EvergreenTree] = {{StageInfo({3,4},1)}}; //TODO: earlier stages
	lt[TropicalTree] = {{ {{5,3},1} }}; //TODO
	lt[Cactus] = {{ }}; // TODO
	lt[Grapevine] = {{StageInfo(), }};
	lt[Lettuce] = ;
	lt[Kale] = ;
	lt[Corn] = ;
	lt[Carrot] = ;
	lt[Beets] = ;
	lt[Potato] = ;
	lt[Onion] = ;
	lt[Garlic] = ;
	lt[Cabbage] = ;
	lt[Broccoli] = ;
	lt[Tomato] = ;
	lt[Cucumber] = ;
	lt[Pepper] = ;
	lt[BlackPepper] = ;
	lt[Cotton] = ;
	lt[Hemp] = ;
	lt[Flax] = ;
	lt[Woad] = ;
	lt[Madder] = ;
	lt[Indigo] = ;
	lt[Lavender] = ;
	lt[Mint] = ;
	lt[Thyme] = ;
	lt[Sage] = ;
	lt[Ginseng] = ;
	lt[Rhubarb] = ;
	lt[Poppy] = ;
	lt[Cocoa] = ;
	lt[Senna] = ;
	lt[Saffron] = ;
	lt[AloeVera] = ;
	lt[Orange] = ;
	lt[Apple] = ;
	lt[Lemon] = ;
	lt[Pear] = ;
	lt[Peach] = ;
	lt[Cherry] = ;
	lt[Apricot] = ;
	lt[Plum] = ;
	lt[Lime] = ;
	lt[Blueberry] = ;
	lt[Strawberry] = ;
	lt[Grape] = ;
	lt[Olive] = ;
	return lt;
}();

inline constexpr LookupTable<Item,SDL_Rect> itemSpriteDimensions = [] {
	LookupTable<Item,SDL_Rect> lt{};
	using enum Item;
	lt[Log] = ;
	lt[Fruit] = ;
	lt[Seed] = ;
	lt[Juice] = ;
	lt[AlcoholicDrink] = ;
	lt[AgedAlcoholicDrink] = ;
	lt[Metal] = ;
	lt[Corpse] = ;
	lt[Gem] = ;
	lt[GreaterGem] = ;
	lt[Ore] = ;
	lt[Ingot] = ;
	lt[CuredHide] = ;
	lt[TannedHide] = ;
	lt[RawMeat] = ;
	lt[CookedMeat] = ;
	lt[CandiedFruit] = ;
	lt[Saltwater] = ;
	lt[Rock] = ;
	lt[Pebble] = ;
	lt[LargeRock] = ;
	lt[Boulder] = ;
	lt[Stick] = ;
	lt[LargeStick] = ;
	lt[LoamSoil] = ;
	lt[SiltySoil] = ;
	lt[SandySoil] = ;
	lt[ClaySoil] = ;
	lt[Podzol] = ;
	lt[PeatSoil] = ;
	lt[RockySoil] = ;
	lt[Oxisol] = ;
	lt[Stone] = ;
	lt[Flint] = ;
	lt[Gravel] = ;
	lt[FruitPit] = ;
	lt[ArsenicOre] = ;
	lt[Milk] = ;
	lt[GoatMilk] = ;
	lt[CamelMilk] = ;
	lt[ChickenEgg] = ;
	lt[DuckEgg] = ;
	lt[TurtleEgg] = ;
	lt[Fish] = ;
	lt[Shellfish] = ;
	lt[Honey] = ;
	lt[RawWax] = ;
	lt[Wax] = ;
	lt[Resin] = ;
	lt[Wool] = ;
	lt[RawSalt] = ;
	lt[Olive] = ;
	lt[Sugarcane] = ;
	lt[Coconut] = ;
	lt[Truffle] = ;
	lt[Wheat] = ;
	lt[Oat] = ;
	lt[Corn] = ;
	lt[Rice] = ;
	lt[Tomato] = ;
	lt[Onion] = ;
	lt[Potato] = ;
	lt[Cabbage] = ;
	lt[Pumpkin] = ;
	lt[Pepper] = ;
	lt[Carrot] = ;
	lt[Poppy] = ;
	lt[Cannabis] = ;
	lt[Senna] = ;
	lt[Cotton] = ;
	lt[Papyrus] = ;
	lt[Flax] = ;
	lt[Hemp] = ;
	lt[Lettuce] = ;
	lt[Cocoa] = ;
	lt[Cucumber] = ;
	lt[Kale] = ;
	lt[Beets] = ;
	lt[Madder] = ;
	lt[Indigo] = ;
	lt[Saffron] = ;
	lt[Ginseng] = ;
	lt[Garlic] = ;
	lt[Sage] = ;
	lt[Mint] = ;
	lt[Thyme] = ;
	lt[Syrup] = ;
	lt[Lavender] = ;
	lt[TreeResin] = ;
	lt[Rhubarb] = ;
	lt[SaltWater] = ;
	lt[Water] = ;
	lt[Sand] = ;
	lt[Clay] = ;
	lt[Tribalwear] = ;
	lt[PrimitiveString] = ;
	lt[PrimitiveNeedle] = ;
	lt[Torch] = ;
	lt[HandAxe] = ;
	lt[StickSpear] = ;
	lt[Hammerstone] = ;
	lt[SharpStone] = ;
	lt[HandKnife] = ;
	lt[HandDrill] = ;
	lt[HandChisel] = ;
	lt[Ash] = ;
	lt[Straw] = ;
	lt[Hay] = ;
	lt[Soot] = ;
	lt[Fiber] = ;
	lt[AnimalHides] = ;
	lt[Feather] = ;
	lt[AnimalHair] = ;
	lt[Bone] = ;
	lt[Sinew] = ;
	lt[Peat] = ;
	lt[Salt] = ;
	lt[DrinkingWater] = ;
	lt[AnimalFat] = ;
	lt[PrimitiveRope] = ;
	lt[PrimitiveSack] = ;
	lt[PrimitiveChair] = ;
	lt[PrimitiveStool] = ;
	lt[LargeSatchel] = ;
	lt[Satchel] = ;
	lt[Javelin] = ;
	lt[SmoothedPebbles] = ;
	lt[Earring] = ;
	lt[Ring] = ;
	lt[EngravedRing] = ;
	lt[Bracelet] = ;
	lt[EngravedBracelet] = ;
	lt[Necklace] = ;
	lt[WoodCrown] = ;
	lt[Sling] = ;
	lt[LargeHandle] = ;
	lt[SmallHandle] = ;
	lt[BoneArtifact] = ;
	lt[PrimitiveAxe] = ;
	lt[PrimitiveAxeHead] = ;
	lt[PrimitiveSpear] = ;
	lt[PrimitiveSpearHead] = ;
	lt[DiggingStick] = ;
	lt[Arrowhead] = ;
	lt[SolidWheel] = ;
	lt[Strap] = ;
	lt[PackedEarth] = ;
	lt[PrimitiveArrow] = ;
	lt[PrimitiveBow] = ;
	lt[Basket] = ;
	lt[LargeBasket] = ;
	lt[Waterskin] = ;
	lt[SaltedRawMeat] = ;
	lt[SaltedCookedMeat] = ;
	lt[SaltedVegetable] = ;
	lt[Thread] = ;
	lt[Yarn] = ;
	lt[String] = ;
	lt[BackstrapLoom] = ;
	lt[ClayJar] = ;
	lt[ClayPot] = ;
	lt[ClayBowl] = ;
	lt[Whip] = ;
	lt[Fertilizer] = ;
	lt[FishMeal] = ;
	lt[BoneMeal] = ;
	lt[Daub] = ;
	lt[WheatGrain] = ;
	lt[Cloth] = ;
	lt[DecorativeCloth] = ;
	lt[Silk] = ;
	lt[Linen] = ;
	lt[Charcoal] = ;
	lt[Cob] = ;
	lt[Wood] = ;
	lt[LogBeam] = ;
	lt[Beam] = ;
	lt[Timber] = ;
	lt[Plank] = ;
	lt[Cheese] = ;
	lt[GoatCheese] = ;
	lt[Butter] = ;
	lt[Flour] = ;
	lt[Sugar] = ;
	lt[Grist] = ;
	lt[MilledRice] = ;
	lt[WoodArtifact] = ;
	lt[Arrow] = ;
	lt[Shortbow] = ;
	lt[ArrowShaft] = ;
	lt[AxeHead] = ;
	lt[ShovelHead] = ;
	lt[SawHead] = ;
	lt[ArdHead] = ;
	lt[ScytheHead] = ;
	lt[HandaxeHead] = ;
	lt[SwordHead] = ;
	lt[MacheteHead] = ;
	lt[CleaverHead] = ;
	lt[TrowelHead] = ;
	lt[ChiselHead] = ;
	lt[HammerHead] = ;
	lt[ScalpelHead] = ;
	lt[MalletHead] = ;
	lt[AdzeHead] = ;
	lt[AwlHead] = ;
	lt[SickleHead] = ;
	lt[KnifeHead] = ;
	lt[StoneTablet] = ;
	lt[FiredClay] = ;
	lt[Pot] = ;
	lt[Kettle] = ;
	lt[Jar] = ;
	lt[Bowl] = ;
	lt[OilLamp] = ;
	lt[Incense] = ;
	lt[BrickMould] = ;
	lt[Rivet] = ;
	lt[Socket] = ;
	lt[Wedge] = ;
	lt[Peg] = ;
	lt[Nail] = ;
	lt[LargeAxle] = ;
	lt[Axle] = ;
	lt[Glue] = ;
	lt[TanningAgent] = ;
	lt[HeavyTannedHides] = ;
	lt[Mortar] = ;
	lt[Plaster] = ;
	lt[SugarJuice] = ;
	lt[Mead] = ;
	lt[Cider] = ;
	lt[FruitWine] = ;
	lt[Wine] = ;
	lt[Beer] = ;
	lt[TemporaryTablet] = ;
	lt[Carpet] = ;
	lt[JoinedPlank] = ;
	lt[CurvedStone] = ;
	lt[CutStoneSheet] = ;
	lt[CutStone] = ;
	lt[CrushedStone] = ;
	lt[JoinedBeam] = ;
	lt[LongStave] = ;
	lt[Stave] = ;
	lt[Bread] = ;
	lt[CornOil] = ;
	lt[CookingOil] = ;
	lt[OliveOil] = ;
	lt[BlueCheese] = ;
	lt[Porridge] = ;
	lt[PickledFruit] = ;
	lt[PickledVegetable] = ;
	lt[Parchment] = ;
	lt[Blowpipe] = ;
	lt[StoneArtifact] = ;
	lt[Bleach] = ;
	lt[YellowDye] = ;
	lt[BlueDye] = ;
	lt[RedDye] = ;
	lt[HandheldBellows] = ;
	lt[Chair] = ;
	lt[Stool] = ;
	lt[ArtificialBeehive] = ;
	lt[Keg] = ;
	lt[Bottle] = ;
	lt[Scroll] = ;
	lt[Horseshoes] = ;
	lt[OxSaddle] = ;
	lt[HorseSaddle] = ;
	lt[GoldCrown] = ;
	lt[FancyClothes] = ;
	lt[FormalClothes] = ;
	lt[Sword] = ;
	lt[ToolHeadPlaceholder] = ;
	lt[ToolHeadMouldPlaceholder] = ;
	lt[ToolPlaceholder] = ;
	lt[WeaponHeadPlaceholder] = ;
	lt[WeaponHeadMouldPlaceholder] = ;
	lt[WeaponPlaceholder] = ;
	lt[PermanentSpearHeadMould] = ;
	lt[SpearHeadMould] = ;
	lt[PermanentPickaxeHeadMould] = ;
	lt[PickaxeHeadMould] = ;
	lt[PermanentAxeHeadMould] = ;
	lt[AxeHeadMould] = ;
	lt[PermanentShovelHeadMould] = ;
	lt[ShovelHeadMould] = ;
	lt[PermanentSawHeadMould] = ;
	lt[SawHeadMould] = ;
	lt[PermanentArdHeadMould] = ;
	lt[ArdHeadMould] = ;
	lt[PermanentScytheHeadMould] = ;
	lt[ScytheHeadMould] = ;
	lt[PermanentHandaxeHeadMould] = ;
	lt[HandaxeHeadMould] = ;
	lt[PermanentSwordHeadMould] = ;
	lt[SwordHeadMould] = ;
	lt[PermanentMacheteHeadMould] = ;
	lt[MacheteHeadMould] = ;
	lt[PermanentCleaverHeadMould] = ;
	lt[CleaverHeadMould] = ;
	lt[PermanentTrowelHeadMould] = ;
	lt[TrowelHeadMould] = ;
	lt[PermanentChiselHeadMould] = ;
	lt[ChiselHeadMould] = ;
	lt[PermanentHammerHeadMould] = ;
	lt[HammerHeadMould] = ;
	lt[ScalpelHeadMould] = ;
	lt[PermanentScalpelHeadMould] = ;
	lt[MalletHeadMould] = ;
	lt[PermanentMalletHeadMould] = ;
	lt[AdzeHeadMould] = ;
	lt[PermanentAdzeHeadMould] = ;
	lt[AwlHeadMould] = ;
	lt[PermanentAwlHeadMould] = ;
	lt[SickleHeadMould] = ;
	lt[PermanentSickleHeadMould] = ;
	lt[PermanentKnifeHeadMould] = ;
	lt[KnifeHeadMould] = ;
	lt[Poison] = ;
	lt[Cyanide] = ;
	lt[Arsenic] = ;
	lt[Hemlock] = ;
	lt[Bandage] = ;
	lt[Laxative] = ;
	lt[MedicinalSoap] = ;
	lt[GileadBalm] = ;
	lt[Theriac] = ;
	lt[Tube] = ;
	lt[Sail] = ;
	lt[Wheel] = ;
	lt[Needles] = ;
	lt[Clips] = ;
	lt[Paper] = ;
	lt[Ink] = ;
	lt[DyedCloth] = ;
	lt[Rope] = ;
	lt[RopemakingFrame] = ;
	lt[Bricks] = ;
	lt[Lime] = ;
	lt[GroundBlackPepper] = ;
	lt[ChiliPowder] = ;
	lt[TruffleOil] = ;
	lt[Vinegar] = ;
	lt[Pastry] = ;
	lt[Airbag] = ;
	lt[FloorLoom] = ;
	lt[Loom] = ;
	lt[Tabletop] = ;
	lt[Bucket] = ;
	lt[Crucible] = ;
	lt[MashTun,] = ;
	lt[Book] = ;
	lt[BasicClothes] = ;
	lt[Axe] = ;
	lt[Spear] = ;
	lt[Bow] = ;
	lt[SpearHead] = ;
	lt[PickaxeHead] = ;
	lt[Die] = ;
	lt[Tonic] = ;
	lt[Elactuarium] = ;
	lt[Trigger] = ;
	lt[Gear] = ;
	lt[Wick] = ;
	lt[NailHeader] = ;
	lt[Glass] = ;
	lt[Soap] = ;
	lt[ColoredPane] = ;
	lt[Pane] = ;
	lt[Concrete] = ;
	lt[Pie] = ;
	lt[GreatswordHead] = ;
	lt[Coins] = ;
	lt[CoinBlank] = ;
	lt[Lens] = ;
	lt[CoinMould] = ;
	lt[Wire] = ;
	lt[SpinningWheel] = ;
	lt[Whorl] = ;
	lt[Candle] = ;
	lt[Chainmail] = ;
	lt[EmperorsStaff] = ;
	lt[RoyalCrown] = ;
	lt[Pike] = ;
	lt[Halberd] = ;
	lt[Greataxe] = ;
	lt[Longbow] = ;
	lt[Crossbow] = ;
	lt[PermanentPikeHeadMould] = ;
	lt[PikeHeadMould] = ;
	lt[PikeHead] = ;
	lt[PermanentHalberdHeadMould] = ;
	lt[HalberdHeadMould] = ;
	lt[HalberdHead] = ;
	lt[PermanentGreataxeHeadMould] = ;
	lt[GreataxeHeadMould] = ;
	lt[GreataxeHead] = ;
	lt[PermanentGreatswordHeadMould] = ;
	lt[GreatswordHeadMould] = ;
	lt[Gambeson] = ;
	lt[Coat] = ;
	lt[Breastplate] = ;
	lt[Helmet] = ;
	lt[Bracers] = ;
	lt[Boots] = ;
	lt[Guards] = ;
	lt[Gloves] = ;
	lt[SmallSculpture] = ;
	lt[SmallPaintedSculpture] = ;
	lt[SmallCarving] = ;
	lt[SmallPaintedCarving] = ;
	lt[Vase] = ;
	lt[PlayScript] = ;
	lt[PaperPainting] = ;
	lt[CanvasPainting] = ;
	lt[GemSeal] = ;
	lt[CutGem] = ;
	lt[CutGreaterGem] = ;
	lt[PaintedGlass] = ;
	lt[Map] = ;
	lt[Pamphlet] = ;
	lt[ShortStory] = ;
	lt[Novel] = ;
	lt[Decree] = ;
	return lt;
}();
