#include "render.hpp"
#include <data/game/screen.hpp>
#include <data/run/texture.hpp>
#include <display/render/sprite.hpp>

// TODO: right now this is only fitted for walk animations. need to make sure
// all the LOGIC is only fitted for walk animations, for now.

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

inline SDL_Rect get_animal_rect(Animal a, FrameData as, Time age, sprite::Info& asi)
{
	bool child = age <animal::FERTILITY_AGES[a];
	SDL_Rect sprite_set = sprite::animals[a];
	int x = sprite_set.x;
	ActState ac = as.get<ActState>();
	Frame frame = as.get<Frame>();
	if (child)
		x += get_child_sprite_offset(asi);
	x += get_action_sprite_offset(asi, ac);
	Direction d = as.get<Direction>();
	x += get_direction_sprite_offset(asi, d, child);

	Coord c = get_sprite_dimensions(asi, d, child);
	int y = sprite_set.y + get_frame_sprite_offset(asi, ac, frame, c.y);

	return {x, y, static_cast<int>(c.x), static_cast<int>(c.y)};
}

inline Frame get_next_animal_frame(Animal a, ActState as, Frame frame_number, sprite::Info& asi)
{
	uint8_t frame = static_cast<uint8_t>(frame_number);
	switch (as)
	{
        //TODO: act
	case ActState::Act:
	case ActState::NewPath:
		frame = 0;
		break;
	case ActState::Walk:
		if (frame++ > asi.walk_sprite_frame_length)
			frame = 0;
		break;
	case ActState::Run:
		if (frame++ > asi.run_sprite_frame_length)
			frame = 0;
		break;
	default:
		break;
	}
	return static_cast<Frame>(frame);
}

void update_animal_animations(MovablesRenderBuffer &erd, Array<FrameData> &frame_datas,
			    Array<Time> &ages)
{
	for (size_t i = 0; i < erd.animal_amount; i++)
	{
		AnimalRenderData ard = erd.animals[i];
		uint16_t ai = ard.index;
		FrameData& fd = frame_datas[i];
		sprite::Info asi = sprite::ANIMAL_SPRITE_INFOS[ard.animal];
		SDL_Rect r = get_animal_rect(ard.animal, fd, ages[ai], asi);
		SDL_Point p = get_camera_relative_point_from_coord(ard.position);
		SDL_Rect dst = {p.x, p.y, r.x, r.y};
		SDL_RenderCopy(renderer, nullptr, &r, &dst);
		//TODO: may not trigger frame advance. need to be planning animation just like we plan path, in a seperate buffer
		fd.set<Frame>(get_next_animal_frame(ard.animal, fd.get<ActState>(), fd.get<Frame>(), asi));
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
			if (frame++ > sprite::UNIT_SPRITE_INFO.walk_sprite_frame_length)
			frame = 0;
		break;
		// TODO: RUN
	case ActState::Run:
			if (frame++ > sprite::UNIT_SPRITE_INFO.run_sprite_frame_length)
			frame = 0;
		break;
        // TODO: implement		
        // case ActState::Act:
	// 	if (frame++ > asi.ACT_SPRITE_FRAME_LENGTH) 
	// 		frame = 0;
	// 	break;
	default:
          break;
	}
	return static_cast<Frame>(frame);
}

//TODO: elderly, skin
inline SDL_Rect get_unit_rect(Unit unit, ActState state, Direction direction, Frame frame, Time age)
{
        bool child = false;
	if (age < MATURITY_AGE)
	{
          child = true;
	} else if (age < ELDER_AGE) {

	}
	SDL_Rect sprite_set = sprite::units[unit];
	int x = sprite_set.x;
	sprite::Info usi = sprite::UNIT_SPRITE_INFO;
	x += get_action_sprite_offset(usi, state);
	x += get_direction_sprite_offset(usi, direction, child);

	Coord c = get_sprite_dimensions(usi, direction, child);
	int y = sprite_set.y + get_frame_sprite_offset(usi, state, frame, c.y);

	return {x, y, static_cast<int>(c.x), static_cast<int>(c.y)};
}

void update_unit_animations(MovablesRenderBuffer &erd, Array<Time> &ages, Array<FrameData> &frame_datas)
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
		SDL_Point p = get_camera_relative_point_from_coord(ard.position);
		SDL_Rect dst = {p.x, p.y, r.x, r.y};
		SDL_RenderCopy(renderer, nullptr, &r, &dst);
		// TODO: may not trigger frame advance. need to be planning animation just like we plan path, in a seperate buffer
		frame_datas[ai].set<Frame>(get_next_unit_frame(ard.unit, state, frame));		
	}
}


//renders entites which can't be chunked
void render_moving_entities(Array<Time> &animal_ages, Array<FrameData> &animal_frames, Array<FrameData>& unit_frame_data, Array<Time> &unit_ages, MovablesRenderBuffer& movables_render_buffer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	update_animal_animations(movables_render_buffer, animal_frames, animal_ages);
	update_unit_animations(movables_render_buffer, unit_ages, unit_frame_data);

	// TODO: draw equippables
	
	// TODO: draw alternate items

	//TODO: upscale
}
