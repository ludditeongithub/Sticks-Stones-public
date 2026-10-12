#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SDL2/SDL_rect.h>
#include <core/containers.hpp>
#include <core/coord.hpp>
#include <data/types/entity.hpp>
#include <cstdint>
#include <data/types/animal.hpp>
#include <data/types/tile.hpp>
#include <data/types/time.hpp>
#include <data/const/animal_tables.hpp>
#include <data/types/unit.hpp>
#include <data/types/action.hpp>
#include "sprite.hpp"
// TODO: sex offsets!
// TODO: perhaps walking frames last for twice as long as running frames

template <typename T>
void update_animations(Array<Coord> &coords, Array<Frame> &frames, Array<T> &states);

const Frame walk_animation_sprite_length = 4;
const Frame run_animation_sprite_length = 8;

// TODO: right now this is only fitted for walk animations. need to make sure
// all the LOGIC is only fitted for walk animations, for now.

inline uint16_t get_action_sprite_offset(sprite::Info &info, ActState state);

inline uint16_t get_child_sprite_offset(sprite::Info &ai);

inline uint16_t get_direction_sprite_offset(sprite::Info &asi, Direction d, bool child);

inline uint16_t get_frame_sprite_offset(sprite::Info &asi, ActState as, Frame frame_number, uint16_t sprite_height);

inline Coord get_sprite_dimensions(sprite::Info &asi, Direction d, bool child);

inline SDL_Rect get_animal_rect(Animal a, FrameData as, Time age, sprite::Info& asi);

inline Frame get_next_animal_frame(Animal a, ActState as, Frame frame_number, sprite::Info& asi);

void update_animal_animations(EntityRenderBuffer &erd, Array<FrameData> &frame_datas, Array<Time> &ages);

inline Frame get_next_unit_frame(Unit u, ActState as, Frame frame_number);

//TODO: elderly, skin
inline SDL_Rect get_unit_rect(Unit unit, ActState state, Direction direction, Frame frame, Time age);

void update_unit_animations(EntityRenderBuffer &erd, Array<Time> &ages, Array<FrameData> &frame_datas);

#endif
