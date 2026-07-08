#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "texture.hpp"
#include <SDL2/SDL_rect.h>
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/entity.hpp>
#include <cstdint>
#include <systems/find_nearest.hpp>
#include <world/animal/enum.hpp>
#include <world/animal/tables.hpp>
#include <world/tile/enum.hpp>
#include <world/unit/enum.hpp>
#include "sprite.hpp"
// TODO: sex offsets!
// TODO: perhaps walking frames last for twice as long as running frames

template <typename T>
void updateAnimations(Array<Coord> &coords, Array<Frame> &frames, Array<T> &states);

const Frame WALK_ANIMATION_SPRITE_LENGTH = Frame::F4;
const Frame RUN_ANIMATION_SPRITE_LENGTH = Frame::F8;

// TODO: right now this is only fitted for walk animations. need to make sure
// all the LOGIC is only fitted for walk animations, for now.


inline uint16_t getActionSpriteOffset(SpriteInfo &ai, ActionStatus as)
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
		return ai.WALKING_SPRITE_LENGTH;
		break;
	default:
		break;
	}
	// TODO: PerformAction, set of actions, be sure to update child sprite offset!
}

inline uint16_t getActionSpriteOffset(SpriteInfo &info, ActState state) {
	switch (state)
	{
		// WALK
	case ActState::Walk:
        case ActState::NewPath:
		return 0;
		break;
		// TODO: RUN
	case ActState::Run:
		return info.WALKING_SPRITE_LENGTH;
		break;
        case ActState::Act:
		return info.WALKING_SPRITE_LENGTH + info.RUNNING_SPRITE_LENGTH;
		break;
	default:
		break;
	}
}

inline uint16_t getChildSpriteOffset(SpriteInfo &ai)
{
	return ai.WALKING_SPRITE_LENGTH + ai.RUNNING_SPRITE_LENGTH;
}

inline uint16_t getDirectionSpriteOffset(SpriteInfo &asi, Direction d, bool child)
{
	uint16_t dOffset = 0;
	if (child)
	{
		switch (d)
		{
		case Direction::South:
			dOffset = 0;
			break;
		case Direction::West:
			dOffset = asi.CHILD_FRONT_LENGTH;
			break;
		case Direction::East:
			dOffset = asi.CHILD_FRONT_LENGTH + asi.CHILD_SIDE_LENGTH;
			break;
		case Direction::North:
			dOffset = asi.CHILD_FRONT_LENGTH + asi.CHILD_SIDE_LENGTH * 2;
			break;
		}
	}
	else
	{
		switch (d)
		{
		case Direction::South:
			dOffset = 0;
			break;
		case Direction::West:
			dOffset = asi.FRONT_LENGTH;
			break;
		case Direction::East:
			dOffset = asi.FRONT_LENGTH + asi.SIDE_LENGTH;
			break;
		case Direction::North:
			dOffset = asi.FRONT_LENGTH + asi.SIDE_LENGTH * 2;
			break;
		}
	}
	return dOffset;
}

inline uint16_t getFrameSpriteOffset(SpriteInfo &asi, ActionStatus as, Frame frameNumber, uint16_t spriteHeight)
{
	uint8_t frame = static_cast<uint8_t>(frameNumber);
	switch (as)
	{
		// WALK
	case ActionStatus::Approach:
		// TODO: sometimes idle moves, sometimes it does not
	case ActionStatus::Idle:
	case ActionStatus::ReturnHome:
	case ActionStatus::Prowl:
		return spriteHeight * (frame / asi.WALK_SPRITE_FRAME_LENGTH);
		break;
		// TODO: RUN
	case ActionStatus::Pursuit:
	case ActionStatus::Flee:
		return spriteHeight * (frame / asi.RUN_SPRITE_FRAME_LENGTH);
		break;	
	}	
}

inline uint16_t getFrameSpriteOffset(SpriteInfo &asi, ActState as, Frame frameNumber,
				     uint16_t spriteHeight)
{
	uint8_t frame = static_cast<uint8_t>(frame);
	switch (as)
	{
		// WALK
	case ActState::Walk:
		// TODO: sometimes idle moves, sometimes it does not
		return spriteHeight * (frame / asi.WALK_SPRITE_FRAME_LENGTH);
		break;
		// TODO: RUN
	case ActState::Run:
		return spriteHeight * (frame / asi.RUN_SPRITE_FRAME_LENGTH);
		break;
        case ActState::Act:
		return spriteHeight * (frame / asi.RUN_SPRITE_FRAME_LENGTH);
		break;
        case ActState::NewPath:
		return 0;
		break;
	default:
		break;
	}
}


inline Coord getSpriteDimensions(SpriteInfo &asi, Direction d, bool child)
{
	uint16_t h = 0;
	uint16_t w = 0;
	if (child)
	{
		switch (d)
		{
		case Direction::North:
		case Direction::South:
			w = asi.CHILD_FRONT_LENGTH;
			h = asi.CHILD_FRONT_HEIGHT;
			break;
		case Direction::East:
		case Direction::West:
			w = asi.CHILD_SIDE_LENGTH;
			h = asi.CHILD_SIDE_HEIGHT;
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
			w = asi.SIDE_LENGTH;
			h = asi.FRONT_HEIGHT;
			break;
		case Direction::East:
		case Direction::West:
			w = asi.FRONT_LENGTH;
			h = asi.SIDE_HEIGHT;
			break;
		default:
			break;
		}
	}
	return {w, h};
}

SDL_Rect getAnimalRect(Animal a, AnimalStatus as, Time age, Frame frame, SpriteInfo& asi)
{
	bool child = age < animal::fertilityAges[a];
	SDL_Rect spriteSet = sprite::animalSprites[a];
	int x = spriteSet.x;
	ActionStatus ac = as.get<ActionStatus>();
	if (child)
		x += getChildSpriteOffset(asi);
	x += getActionSpriteOffset(asi, ac);
	Direction d = as.get<Direction>();
	x += getDirectionSpriteOffset(asi, d, child);

	Coord c = getSpriteDimensions(asi, d, child);
	int y = spriteSet.y + getFrameSpriteOffset(asi, ac, frame, c.y);

	return {x, y, static_cast<int>(c.x), static_cast<int>(c.y)};
}

inline Frame getNextAnimalFrame(Animal a, ActionStatus as, Frame frameNumber, SpriteInfo& asi)
{
		uint8_t frame = static_cast<uint8_t>(frameNumber);
	switch (as)
	{
		// WALK
	case ActionStatus::Approach:
		// TODO: sometimes idle moves, sometimes it does not
	case ActionStatus::Idle:
	case ActionStatus::ReturnHome:
	case ActionStatus::Prowl:
		if (frame++ > asi.WALK_SPRITE_FRAME_LENGTH)
			frame = 0;
		break;
		// TODO: RUN
	case ActionStatus::Pursuit:
	case ActionStatus::Flee:
		if (frame++ > asi.RUN_SPRITE_FRAME_LENGTH)
			frame = 0;
		break;
	default:
		break;
	}
	return static_cast<Frame>(frame);
}

void updateAnimalAnimations(Coord leftCorner, EntityRenderBuffer &erd, Array<Frame> &frames,
			    Array<Time> &ages, Array<AnimalStatus> &states)
{
	for (size_t i = 0; i < erd.animalAmount; i++)
	{
		AnimalRenderData ard = erd.animals[i];
		uint16_t ai = ard.index;
		Frame &f = frames[ai];
		AnimalStatus &s = states[ai];
		SpriteInfo asi = animalSpriteInfos[ard.animal];
		SDL_Rect r = getAnimalRect(ard.animal, s, ages[ai], f, asi);

		// TODO: position must be relative to screen
		spriteSheetTexture.render(ard.position.x, ard.position.y, &r, &mainScreenViewport);
		
		f = getNextAnimalFrame(ard.animal, s.get<ActionStatus>(), f, asi);
	}
}

inline Frame getNextUnitFrame(Unit u, ActState as, Frame frameNumber)
{
	uint8_t frame = static_cast<uint8_t>(frameNumber);
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
		if (frame++ > UNIT_SPRITE_INFO.WALK_SPRITE_FRAME_LENGTH)
			frame = 0;
		break;
		// TODO: RUN
	case ActState::Run:
		if (frame++ > UNIT_SPRITE_INFO.RUN_SPRITE_FRAME_LENGTH)
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

inline SDL_Rect getUnitRect(Unit unit, ActState state, Direction direction, Frame frame, Time age) {
	bool child = age < MATURITY_AGE;
	SDL_Rect spriteSet = sprite::unitSprites[];
	int x = spriteSet.x;
	SpriteInfo usi = UNIT_SPRITE_INFO;
	if (child) x += getChildSpriteOffset(usi);
	x += getActionSpriteOffset(usi, state);
	x += getDirectionSpriteOffset(usi, direction, child);

	Coord c = getSpriteDimensions(usi, direction, child);
	int y = spriteSet.y + getFrameSpriteOffset(usi, state, frame, c.y);

	return {x, y, static_cast<int>(c.x), static_cast<int>(c.y)};
}

void updateUnitAnimations(Coord leftCorner, EntityRenderBuffer &erd,
			  Array<Time> &ages, Array<FrameData> &frameDatas)
{
	for (size_t i = 0; i < erd.animalAmount; i++)
	{
		UnitRenderData ard = erd.units[i];
		size_t ai = ard.index;
		ActState state = frameDatas[ai].get<ActState>();
		Direction direction = frameDatas[ai].get<Direction>();
		Frame frame = frameDatas[ai].get<Frame>();
		// TODO: implement skin color
		SDL_Rect r = getUnitRect(ard.unit, state, direction, frame, ages[ai]);
		// TODO: position must be relative to screen
		spriteSheetTexture.render(ard.position.x, ard.position.y, &r, &mainScreenViewport);
		frame = getNextUnitFrame(ard.unit, state, frame);		
	}
}

#endif
