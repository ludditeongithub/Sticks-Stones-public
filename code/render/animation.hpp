#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "texture.hpp"
#include <SDL2/SDL_rect.h>
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/entity.hpp>
#include <cstdint>

#include <world/animal/enum.hpp>
#include <world/animal/tables.hpp>
#include <world/tile/enum.hpp>
#include <world/unit/enum.hpp>
#include "sprite.hpp"
// TODO: sex offsets!
// TODO: perhaps walking frames last for twice as long as running frames

template <typename T>
void update_animations(Array<Coord> &coords, Array<Frame> &frames, Array<T> &states);

const Frame walk_animation_sprite_length = Frame::F4;
const Frame run_animation_sprite_length = Frame::F8;

// TODO: right now this is only fitted for walk animations. need to make sure
// all the LOGIC is only fitted for walk animations, for now.


inline uint16_t get_action_sprite_offset(sprite::Info &ai, ActionStatus as)
{
	switch (as)
	{
		// WALK
	case ActionStatus::Approach:
		// TODO: sometimes idle moves, sometimes it does not
	case ActionStatus::Idle:
	case ActionStatus::ReturnHome:
	case ActionStatus::Prowl:
		return 0;
		break;
		// TODO: RUN
	case ActionStatus::Pursuit:
	case ActionStatus::Flee:
		return ai.walking_sprite_length;
		break;
	default:
		break;
	}
	// TODO: PerformAction, set of actions, be sure to update child sprite offset!
}

inline uint16_t get_action_sprite_offset(sprite::Info &info, ActState state) {
	switch (state)
	{
		// WALK
	case ActState::Walk:
        case ActState::NewPath:
		return 0;
		break;
		// TODO: RUN
	case ActState::Run:
		return info.walking_sprite_length;
		break;
        case ActState::Act:
		return info.walking_sprite_length + info.running_sprite_length;
		break;
	default:
		break;
	}
}

inline uint16_t get_child_sprite_offset(sprite::Info &ai)
{
	return ai.walking_sprite_length + ai.running_sprite_length;
}

inline uint16_t get_direction_sprite_offset(sprite::Info &asi, Direction d, bool child)
{
	uint16_t d_offset = 0;
	if (child)
	{
		switch (d)
		{
		case Direction::South:
			d_offset = 0;
			break;
		case Direction::West:
			d_offset = asi.child_front_length;
			break;
		case Direction::East:
			d_offset = asi.child_front_length + asi.child_side_length;
			break;
		case Direction::North:
			d_offset = asi.child_front_length + asi.child_side_length * 2;
			break;
		}
	}
	else
	{
		switch (d)
		{
		case Direction::South:
			d_offset = 0;
			break;
		case Direction::West:
			d_offset = asi.front_length;
			break;
		case Direction::East:
			d_offset = asi.front_length + asi.side_length;
			break;
		case Direction::North:
			d_offset = asi.front_length + asi.side_length * 2;
			break;
		}
	}
	return d_offset;
}

inline uint16_t get_frame_sprite_offset(sprite::Info &asi, ActionStatus as, Frame frame_number, uint16_t sprite_height)
{
	uint8_t frame = static_cast<uint8_t>(frame_number);
	switch (as)
	{
		// WALK
	case ActionStatus::Approach:
		// TODO: sometimes idle moves, sometimes it does not
	case ActionStatus::Idle:
	case ActionStatus::ReturnHome:
	case ActionStatus::Prowl:
		return sprite_height * (frame / asi.walk_sprite_frame_length);
		break;
		// TODO: RUN
	case ActionStatus::Pursuit:
	case ActionStatus::Flee:
		return sprite_height * (frame / asi.run_sprite_frame_length);
		break;	
	}	
}

inline uint16_t get_frame_sprite_offset(sprite::Info &asi, ActState as, Frame frame_number,
				     uint16_t sprite_height)
{
	uint8_t frame = static_cast<uint8_t>(frame);
	switch (as)
	{
		// WALK
	case ActState::Walk:
		// TODO: sometimes idle moves, sometimes it does not
		return sprite_height * (frame / asi.walk_sprite_frame_length);
		break;
		// TODO: RUN
	case ActState::Run:
		return sprite_height * (frame / asi.run_sprite_frame_length);
		break;
        case ActState::Act:
		return sprite_height * (frame / asi.run_sprite_frame_length);
		break;
        case ActState::NewPath:
		return 0;
		break;
	default:
		break;
	}
}


inline Coord get_sprite_dimensions(sprite::Info &asi, Direction d, bool child)
{
	uint16_t h = 0;
	uint16_t w = 0;
	if (child)
	{
		switch (d)
		{
		case Direction::North:
		case Direction::South:
			w = asi.child_front_length;
			h = asi.child_front_height;
			break;
		case Direction::East:
		case Direction::West:
			w = asi.child_side_length;
			h = asi.child_side_height;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (d)
		{
		case Direction::North:
		case Direction::South:
			w = asi.side_length;
			h = asi.front_height;
			break;
		case Direction::East:
		case Direction::West:
			w = asi.front_length;
			h = asi.side_height;
			break;
		default:
			break;
		}
	}
	return {w, h};
}

SDL_Rect get_animal_rect(Animal a, AnimalStatus as, Time age, Frame frame, sprite::Info& asi)
{
	bool child = age < animal::FERTILITY_AGES[a];
	SDL_Rect sprite_set = sprite::animal[a];
	int x = sprite_set.x;
	ActionStatus ac = as.get<ActionStatus>();
	if (child)
		x += get_child_sprite_offset(asi);
	x += get_action_sprite_offset(asi, ac);
	Direction d = as.get<Direction>();
	x += get_direction_sprite_offset(asi, d, child);

	Coord c = get_sprite_dimensions(asi, d, child);
	int y = sprite_set.y + get_frame_sprite_offset(asi, ac, frame, c.y);

	return {x, y, static_cast<int>(c.x), static_cast<int>(c.y)};
}

inline Frame get_next_animal_frame(Animal a, ActionStatus as, Frame frame_number, sprite::Info& asi)
{
		uint8_t frame = static_cast<uint8_t>(frame_number);
	switch (as)
	{
		// WALK
	case ActionStatus::Approach:
		// TODO: sometimes idle moves, sometimes it does not
	case ActionStatus::Idle:
	case ActionStatus::ReturnHome:
	case ActionStatus::Prowl:
		if (frame++ > asi.walk_sprite_frame_length)
			frame = 0;
		break;
		// TODO: RUN
	case ActionStatus::Pursuit:
	case ActionStatus::Flee:
		if (frame++ > asi.run_sprite_frame_length)
			frame = 0;
		break;
	default:
		break;
	}
	return static_cast<Frame>(frame);
}

void update_animal_animations(Coord left_corner, EntityRenderBuffer &erd, Array<Frame> &frames,
			    Array<Time> &ages, Array<AnimalStatus> &states)
{
	for (size_t i = 0; i < erd.animal_amount; i++)
	{
		AnimalRenderData ard = erd.animals[i];
		uint16_t ai = ard.index;
		Frame &f = frames[ai];
		AnimalStatus &s = states[ai];
		sprite::Info asi = animal_sprite_infos[ard.animal];
		SDL_Rect r = get_animal_rect(ard.animal, s, ages[ai], f, asi);

		// TODO: position must be relative to screen
		sprite_sheet_texture.render(ard.position.x, ard.position.y, &r, &main_screen_viewport);
		
		f = get_next_animal_frame(ard.animal, s.get<ActionStatus>(), f, asi);
	}
}

inline Frame get_next_unit_frame(Unit u, ActState as, Frame frame_number)
{
	uint8_t frame = static_cast<uint8_t>(frame_number);
	switch (as)
	{
		// TODO: change this to play animations for specific actions (maybe a
		// few animations per item, like 'throw', 'hammer', 'hammer against
		// object', 'train', etc)
        case ActState::Act:
	case ActState::NewPath:
		frame = 0;
		break;
		// WALK
	case ActState::Walk:
		if (frame++ > UNIT_SPRITE_INFO.walk_sprite_frame_length)
			frame = 0;
		break;
		// TODO: RUN
	case ActState::Run:
		if (frame++ > UNIT_SPRITE_INFO.run_sprite_frame_length)
			frame = 0;
		break;
        // TODO: implement		
        // case ActState::Act:
	// 	if (frame++ > asi.ACT_SPRITE_FRAME_LENGTH) 
	// 		frame = 0;
	// 	break;
	default:
	}
	return static_cast<Frame>(frame);
}

inline SDL_Rect get_unit_rect(Unit unit, ActState state, Direction direction, Frame frame, Time age) {
	bool child = age < MATURITY_AGE;
	SDL_Rect sprite_set = sprite::unit[];
	int x = sprite_set.x;
	sprite::Info usi = UNIT_SPRITE_INFO;
	if (child) x += get_child_sprite_offset(usi);
	x += get_action_sprite_offset(usi, state);
	x += get_direction_sprite_offset(usi, direction, child);

	Coord c = get_sprite_dimensions(usi, direction, child);
	int y = sprite_set.y + get_frame_sprite_offset(usi, state, frame, c.y);

	return {x, y, static_cast<int>(c.x), static_cast<int>(c.y)};
}

void update_unit_animations(Coord left_corner, EntityRenderBuffer &erd,
			  Array<Time> &ages, Array<FrameData> &frame_datas)
{
	for (size_t i = 0; i < erd.animal_amount; i++)
	{
		UnitRenderData ard = erd.units[i];
		size_t ai = ard.index;
		ActState state = frame_datas[ai].get<ActState>();
		Direction direction = frame_datas[ai].get<Direction>();
		Frame frame = frame_datas[ai].get<Frame>();
		// TODO: implement skin color
		SDL_Rect r = get_unit_rect(ard.unit, state, direction, frame, ages[ai]);
		// TODO: position must be relative to screen
		sprite_sheet_texture.render(ard.position.x, ard.position.y, &r, &main_screen_viewport);
		frame = get_next_unit_frame(ard.unit, state, frame);		
	}
}

#endif
