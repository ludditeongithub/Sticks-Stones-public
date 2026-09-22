namespace order {
enum class Category
{
	Administrative,
	Legal,
	Cultural,
	Satisfaction,
	Force,
	MAX
};
}

namespace knowledge {

enum class Category
{
	Technology, // aka item and buildable recipes. sometimes dependent on units
	Academic,   // increases rate of knowledge
	Exploration,
	Units, // actually allows production of item and buildable recipes
	Foreign,
	MAX
};

enum class Technology {
MAX
};

enum class Academic
{
	// Mathematics
	PositiveArithmetic,
	Zero,
	NegativeNumbers,
	Rationals,
	Exponentials,
	BasicGeometry,
        Algebra,
	Graphing,
	Calculus,
        LinearAlgebra,
        // Natural Philosophy
        // Language/Philosophy
        Rhetoric,
        BasicGrammar,
        Literature,
        Argumentation,
        SyllogisticLogic,
        FormalLogic,
        SymbolicLogic,
        MAX
};

enum class Exploration
{

};

enum class Units
{

};

enum class Foreign
{

};
}
  
enum class Ritual
{
	Song,
	InstrumentalSong,
	Poem,
	Play,
	Story,
	MathematicsText,
	Chronicle,
	HistoryText,
	PhilosophyText,
	LawText,
	ReviewTexts,
	MakeMap,

	LeaderSpeech,
	Debate,
	PublicTeaching,

	KnowledgeBoost,

	MinterBoost,
	BuilderBoost,
	MinerBoost,
	BrewerBoost,
	BakerBoost,
	CharcoalMakerBoost,
	BowyerBoost,
	ButcherBoost,
	CarpenterBoost,
	CraftsmanBoost,
	CuraisserBoost,
	FletcherBoost,
	MasonBoost,
	CookBoost,
	WeaverBoost,
	TeamsterBoost,
	HorseBreederBoost,
	PriestBoost,
	SingleTradeContract,
	RepeatTradeContract,
	CreateTariff,
	Investment,
	CreateTax,
	PayTax,
	Loan,

	EnactLaw,
	ProposeBill,
	PromoteBill,


	Surgery,
	AnimalSurgery,
	DriveChariot,
	Sail,
	AssistSail,
	RaceChariot,
	Judgement,
	Argument,
	Tournament,

	Apprentice,
	Study,
	Teach,
	Caretake,

	Explore,
	Chart,

	Decree,
	AgricultureDecree,

	BlueprintOrder,
	MonumentBlueprintOrder,

	FriendlyLetter,
	RequestAid,
	TradeOffer,
	PeaceTreaty,
	RequestAlliance,
	RequestUnion,
	EncourageWar,
	GatherSpecificForeignInfo,
	WarDeclaration,
	FindMine,
	BuildSpyNetwork,
	CounterSpy,
	InitiationRitual,
	CurryFavor,

	Plow,
	MAX
};

