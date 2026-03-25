#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <core/entity.hpp>
#include "texture.hpp"
#include "viewport.hpp"
#include <SDL2/SDL_rect.h>
#include <core/containers.hpp>
#include <core/data.hpp>
#include <cstdint>
#include <systems/find_nearest.hpp>
#include <world/animal/enum.hpp>
#include <world/tile/enum.hpp>
#include <world/unit/enum.hpp>
// TODO: sex offsets!
// TODO: perhaps walking frames last for twice as long as running frames

template <typename T>
void updateAnimations(Array<Coord> &coords, Array<Frame> &frames, Array<T> &states);

const Frame WALK_ANIMATION_SPRITE_LENGTH = 4;
const Frame RUN_ANIMATION_SPRITE_LENGTH = 8;

// TODO: right now this is only fitted for walk animations. need to make sure
// all the LOGIC is only fitted for walk animations, for now.

struct SpriteInfo
{
	const Coord leftCorner;
	// in tiles
	const uint8_t SIDE_LENGTH;
	const uint8_t SIDE_HEIGHT;
	const uint8_t FRONT_LENGTH;
	const uint8_t FRONT_HEIGHT;
	const uint8_t CHILD_SIDE_LENGTH;
	const uint8_t CHILD_SIDE_HEIGHT;
	const uint8_t CHILD_FRONT_LENGTH;
	const uint8_t CHILD_FRONT_HEIGHT;
	const uint8_t WALKING_SPRITE_LENGTH = SIDE_LENGTH * FRONT_LENGTH * 2;
	const uint8_t RUNNING_SPRITE_LENGTH = SIDE_LENGTH * FRONT_LENGTH * 4;
	const Frame WALK_SPRITE_FRAME_LENGTH;
	const Frame RUN_SPRITE_FRAME_LENGTH;
	const Frame ACT_SPRITE_FRAME_LENGTH;
};

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
	}
	// TODO: PerformAction, set of actions, be sure to update child sprite offset!
}

inline uint16_t getActionSpriteOffset(SpriteInfo &info, ActState state) {
	switch (as)
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
		return info.WALKING_SPRITE_LENGTH + RUNNING_SPRITE_LENGTH;
	default:
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

inline uint16_t getFrameSpriteOffset(SpriteInfo &asi, ActionStatus as, uint16_t frame,
				     uint16_t spriteHeight)
{
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
	default:
	}
}

inline uint16_t getFrameSpriteOffset(SpriteInfo &asi, ActState as, uint16_t frame,
				     uint16_t spriteHeight)
{
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
		}
	}
	return {w, h};
}

SDL_Rect getAnimalRect(Animal a, AnimalStatus as, Time age, Frame frame, SpriteInfo& asi)
{
	bool child = age < maturityAges[a];
	int x = asi.leftCorner.x;
	ActState ac = as.second();
	if (child)
		x += getChildSpriteOffset(asi);
	x += getActionSpriteOffset(asi, ac);
	Direction d = as.first();
	x += getDirectionSpriteOffset(asi, d, child);

	Coord c = getSpriteDimensions(asi, d, child);
	int y = asi.leftCorner.y + getFrameSpriteOffset(asi, ac, frame, c.y);

	return {x, y, static_cast<int>(c.x), static_cast<int>(c.y)};
}

inline Frame getNextUnitFrame(Animal a, ActState as, Frame frame, SpriteInfo& asi)
{
	switch (as)
	{
		// WALK
	case ActState::Walk:
		// TODO: sometimes idle moves, sometimes it does not
		if (frame++ > asi.WALK_SPRITE_FRAME_LENGTH)
			frame = 0;
		break;
		// TODO: RUN
	case ActState::Run:
		if (frame++ > asi.RUN_SPRITE_FRAME_LENGTH)
			frame = 0;
		break;
        case ActState::Act:
		if (frame++ > asi.ACT_SPRITE_FRAME_LENGTH)
			frame = 0;
		break;
	default:
	}
	return frame;
}

void updateAnimalAnimations(Coord leftCorner, EntityRenderBuffer &erd, Array<Frame> &frames,
			    Array<Time> &ages, Array<AnimalStatus> &states)
{
	for (uint16_t i = 0; i < erd.animalAmount; i++)
	{
		AnimalRenderData ard = erd.animals[i];
		uint16_t ai = ard.index;
		Frame &f = frames[ai];
		AnimalStatus &s = states[ai];
		SpriteInfo asi = animalSpriteInfos[a];
		SDL_Rect r = getAnimalRect(ard.animal, s, ages[ai], f, asi);

		// TODO: position must be relative to screen
		gSpriteSheetTexture.render(ard.position.x, ard.position.y, &r, &mainScreenViewport);
		
		f = getNextAnimalFrame(ard.animal, s.second(), f, asi);
	}
}

inline Frame getNextUnitFrame(Unit u, ActState as, Frame frame, SpriteInfo& asi)
{
	switch (as)
	{
	case ActState::Act:
	// TODO: change this to play animations for specific actions (maybe a
		// few animations per item, like 'throw', 'hammer', 'hammer against
		// object', 'train', etc)
	case ActState::NewPath:
		frame = 0;
		break;
		// WALK
	case ActState::Walk:
		if (frame++ > asi.WALK_SPRITE_FRAME_LENGTH)
			frame = 0;
		break;
		// TODO: RUN
	case ActState::Run:
		if (frame++ > asi.RUN_SPRITE_FRAME_LENGTH)
			frame = 0;
		break;
        case ActState::Act:
		if (frame++ > asi.ACT_SPRITE_FRAME_LENGTH) 
			frame = 0;
		break;
	default:
	}
	return frame;
}

inline SDL_Rect getUnitRect(Unit unit, ActionState state, Direction direction, Frame frame, Age age, SpriteInfo& usi) {
	bool child = age < maturityAge;
	int x = usi.leftCorner.x;

	if (child)
        x += getChildSpriteOffset(usi);
	x += getActionSpriteOffset(usi, state);
	x += getDirectionSpriteOffset(usi, d, child);

	Coord c = getSpriteDimensions(usi, d, child);
	int y = usi.leftCorner.y + getFrameSpriteOffset(usi, ac, frame, c.y);

	return {x, y, static_cast<int>(c.x), static_cast<int>(c.y)};
}

void updateUnitAnimations(Coord leftCorner, EntityRenderBuffer &erd,
			  Array<Time> &ages, Array<FrameData> &frameDatas)
{
	for (uint16_t i = 0; i < erd.animalAmount; i++)
	{
		UnitRenderData ard = erd.units[i];
		uint16_t ai = ard.index;
		ActionState state = frameDatas[ai].first();
		Direction direction = frameDatas[ai].second();
		Frame frame = frameDatas[ai].third();
		SpriteInfo usi = unitSpriteInfos[ard.unit];
		SDL_Rect r = getUnitRect(ard.unit, state, direction, frame, ages[ai], usi);
		// TODO: position must be relative to screen
		gSpriteSheetTexture.render(ard.position.x, ard.position.y, &r, &mainScreenViewport);
		f = getNextUnitFrame(ard.unit, state, frame, usi);
	}
}

#endif
