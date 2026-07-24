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
void render_subject_display(Time age, EntityRenderData render_data)
{
	SDL_Rect* subject;
	if (auto animal_data = std::get_if<AnimalRenderData>(&render_data))
	{
		subject = get_animal_rect(animal_data->animal, {Direction::South, ActionStatus::Idle, MatingStatus::Infertile}, age, 0, animal_sprite_infos[animal_data->animal]);
	}
	else if (auto unit_data = std::get_if<UnitRenderData>(&render_data))
	{
		subject = get_unit_rect(unit_data->unit, ActionStatus::Idle, Direction::South, 0, age, unit_sprite_infos[unit_data->unit]);
	}
	sprite_sheet_texture.render(display.x, display.y, subject, &bottom_bar_viewport);
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
	TextBox name_tag;
	TextBox clan_tag;

	BottomUnitBar()
	{
		bars[static_cast<int>(UnitStatusBars::Health)] = StatusBar({8, 314}, , true);
		bars[static_cast<int>(UnitStatusBars::Hunger)] = StatusBar({8, 320}, , false);
		bars[static_cast<int>(UnitStatusBars::Thirst)] = StatusBar({16, 320}, , false);
		bars[static_cast<int>(UnitStatusBars::Satisfaction)] = StatusBar({24, 320}, , false);
		//    bars[static_cast<int>(UnitStatusBars::Social)] = StatusBar({32, 320}, ,false);
		name_tag = 
	}

	void render() {}

	void render_text() {}
};

void instantiate_bottom_unit(bool alt)
{
	// render status bars

	// render nametags

	// render unit display

	// render equipment buttons / display

	// render text buttons

	// render inventory button
}

} // namespace bb
