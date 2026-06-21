#include "core/database.hpp"
#include "world/animal/enum.hpp"
#include <ui/components/status_bar.hpp>
#include <ui/components/text_box.hpp>
#include <ui/components/element.hpp>
#include <core/data.hpp>
#include <render/animation.hpp>
#include <render/texture.hpp>
#include <variant>

// TODO: get clips
namespace bb
{

constexpr int width = SCREEN_WIDTH;
constexpr int height = 55;
constexpr SCoord display = {57, 8};
constexpr SCoord equipment = {96, 9};

using Subject = std::variant<Animal, Unit>;

// TODO: add animation to subject display
void renderSubjectDisplay(Time age, EntityRenderData renderData)
{
	SDL_Rect* subject;
	if (auto animalData = std::get_if<AnimalRenderData>(&renderData))
	{
		subject = getAnimalRect(animalData->animal, {Direction::South, ActionStatus::Idle, MatingStatus::Infertile}, age, 0, animalSpriteInfos[animalData->animal]);
	}
	else if (auto unitData = std::get_if<UnitRenderData>(&renderData))
	{
		subject = getUnitRect(unitData->unit, ActionStatus::Idle, Direction::South, 0, age, unitSpriteInfos[unitData->unit]);
	}
	spriteSheetTexture.render(display.x, display.y, subject, &bottomBarViewport);
}

enum class UnitStatusBars
{
	Health,
	Hunger,
	Thirst,
	Satisfaction,
	MAX
};

class BottomUnitBar
{
	StatusBar bars[static_cast<int>(UnitStatusBars::MAX)];
	TextBox nameTag;
	TextBox clanTag;

	BottomUnitBar()
	{
		bars[static_cast<int>(UnitStatusBars::Health)] = StatusBar({8, 314}, , true);
		bars[static_cast<int>(UnitStatusBars::Hunger)] = StatusBar({8, 320}, , false);
		bars[static_cast<int>(UnitStatusBars::Thirst)] = StatusBar({16, 320}, , false);
		bars[static_cast<int>(UnitStatusBars::Satisfaction)] = StatusBar({24, 320}, , false);
		//    bars[static_cast<int>(UnitStatusBars::Social)] = StatusBar({32, 320}, ,false);
		nameTag = 
	}

	void render() {}

	void renderText() {}
};

void instantiateBottomUnit(bool alt)
{
	// render status bars

	// render nametags

	// render unit display

	// render equipment buttons / display

	// render text buttons

	// render inventory button
}

} // namespace bb
