#pragma once
#include "data/run/camera.hpp"
#include "data/run/plant_database.hpp"
#include "data/types/entity.hpp"
#include <display/render/draw.hpp>
#include <data/run/world.hpp>
#include <logic/simulation/game.hpp>
#include <logic/generic/search/search.hpp>

void render(Game& game)
{
		EntityRenderBuffer erb = g_search->get_all_in_range(g_camera_left_corner, );
// TODO: set new intertias/actions
		render_chunk_texture(g_world, game.tile_database.tileDatas, g_camera_left_corner, erb, game.plant_database);
		
		render_moving_entities(g_world, g_camera_left_corner, game.tile_database.tileDatas, game.animal_database.ages, game.animal_database.frames, game.animal_database.Frame, game.unit_database.frame_datas, game.unit_database.ages, erb);
}
