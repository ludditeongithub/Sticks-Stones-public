#pragma once
#include "data/run/camera.hpp"
#include <core/containers.hpp>
#include <data/types/time.hpp>
#include <data/types/rendering.hpp>
#include <logic/simulation/game.hpp>
#include <logic/generic/search.hpp>

inline void ui_render(int x, int y, )
{

}

void render_chunks_in_view();

void render_moving_entities(Array<Time> &animal_ages, Array<FrameData> &animal_frames, Array<FrameData>& unit_frame_data, Array<Time> &unit_ages, MovablesRenderBuffer& movables_render_buffer);

void render_ui();

void upscale();

void render_text();

void render()
{
                 render_chunks_in_view();
		 MovablesRenderBuffer mrb = g_search->get_all_movables_in_area(g_camera);
		 render_moving_entities(g_game->animal_database.ages, g_game->animal_database.frame_datas, g_game->unit_database.frame_datas, g_game->unit_database.ages, mrb);
}
