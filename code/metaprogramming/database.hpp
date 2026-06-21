#pragma once

#include "constructors.hpp"

//NOTE: the default database contains automatic indexing, fixed capacity and size of up to uint32_t, and graveyard tracking. 

#define BASE_DATABASE_INDEPENDENT_MEMBERS(X)                                                    \
	X(uint32_t, capacity)                                                                      \
	X(uint32_t, size)                                                                          \
X(Stack<size_t>, freeSlots)

#define MOVABLE_DATABASE_INDEPENDENT_MEMBERS(X) \
       X(SearchGrid& search)

#define BASE_DATABASE_RUNTIME_ARRAYS(X)                                                      \
	X(bool, alives, false)                                                                     

#define POSITIONAL_DATABASE_RUNTIME_ARRAYS(X) \
       X(Coord, coords, coord, coord)

#define MOVABLE_DATABASE_RUNTIME_ARRAYS(X) \     
       X(Direction, directions, Direction::South, Direction::South)

#define BASE_DATABASE_DECLARATION(ENTITY_NAME)                                                  \
	BASE_DATABASE_INDEPENDENT_MEMBERS(DECLARE_MEMBER)                                       \
	BASE_DATABASE_RUNTIME_ARRAYS(DECLARE_ARRAY)                                             \
	ENTITY_NAME##_INDEPENDENT_MEMBERS(DECLARE_MEMBER) \
ENTITY_NAME##_STD_CONTAINERS(DECLARE_MEMBER) \
ENTITY_NAME##_RUNTIME_ARRAYS(DECLARE_ARRAY)

#define NEWBORN_ENTITY_SPAWN_SETTINGS(type, container_name, newborn_value, adult_value) \
    container_name[i] = newborn_value;

#define ADULT_ENTITY_SPAWN_SETTINGS(type, container_name, newborn_value, adult_value) \
    container_name[i] = adult_value;

#define POSITIONAL_ENTITY_SPAWN(Entity_name, entity_name, RUNTIME_ARRAYS)                             \
	bool spawn(Entity_name entity_name, Coord coord, bool newborn)                             \
	{                                                                                          \
		if (size + 1 > capacity)                                                           \
			return false;                                                              \
                                                                                                   \
		size_t i;                                                                          \
                                                                                                   \
		if (freeSlots.empty())                                                             \
		{                                                                                  \
			i = size;                                                                  \
			size++;                                                                    \
		}                                                                                  \
		else                                                                               \
		{                                                                                  \
			i = freeSlots.top();                                                       \
			freeSlots.pop();                                                           \
		}                                                                                  \
                                                                                                   \
		alives[i] = true;                                                                  \
		coords[i] = coord;                                                                 \
                                                                                                   \
		if (newborn)                                                                       \
		{                                                                                  \
RUNTIME_ARRAYS(NEWBORN_ENTITY_SPAWN_SETTINGS)                              \
		} \
else { RUNTIME_ARRAYS(ADULT_ENTITY_SPAWN_SETTINGS) }\
 \
    return true; \
}

#define BASE_ENTITY_SPAWN(Entity_name, entity_name, RUNTIME_ARRAYS)                             \
	bool spawn(Entity_name entity_name, bool newborn)                             \
	{                                                                                          \
		if (size + 1 > capacity)                                                           \
			return false;                                                              \
                                                                                                   \
		size_t i;                                                                          \
                                                                                                   \
		if (freeSlots.empty())                                                             \
		{                                                                                  \
			i = size;                                                                  \
			size++;                                                                    \
		}                                                                                  \
		else                                                                               \
		{                                                                                  \
			i = freeSlots.top();                                                       \
			freeSlots.pop();                                                           \
		}                                                                                  \
                                                                                                   \
		alives[i] = true;                                                                  \
                                                                                                   \
		if (newborn)                                                                       \
		{                                                                                  \
RUNTIME_ARRAYS(NEWBORN_ENTITY_SPAWN_SETTINGS)                              \
		} \
else { RUNTIME_ARRAYS(ADULT_ENTITY_SPAWN_SETTINGS) }\
 \
    return true; \
}


#define BASE_ENTITY_DELETE()                                                                    \
	bool remove(size_t i)                                                                      \
	{                                                                                          \
		if (!alives[i])                                                                    \
			return false;                                                              \
                                                                                                   \
		freeSlots.push(i);                                                                 \
		alives[i] = false;                                                                 \
search.deleteEntity                                                                                                   \
		return true;                                                                       \
		}

#define BASE_ATTEMPT_MOVE_ENTITY() \
inline bool attemptMoveEntity(size_t index) \
{ \
  Coord& pos = coords[index]; \
  Coord newPos = getPos(directions[index], pos); \
  size_t ti = world.getTileIndexFromCoord(newPos); \
  if (search->tiles->occupieds[ti] == false) \
    { \
      pos = newPos; \
    } else return false; \
}

#define SERIALIZE_BINARY_FIELD(type, field) \
    archive(field);

#define SAVE_BINARY_RUNTIME_ARRAY(type, field, ...) \
    field.save(archive);

#define LOAD_BINARY_RUNTIME_ARRAY(type, field, ...) \
    field.load(archive);

#define BASE_STRUCT_SERIALIZATION(ENTITY_NAME)                                              \
    template <class Archive> void save(Archive &archive) const                                 \
    {                                                                                          \
        BASE_DATABASE_INDEPENDENT_MEMBERS(SERIALIZE_BINARY_FIELD)                           \
        BASE_DATABASE_RUNTIME_ARRAYS(SAVE_BINARY_RUNTIME_ARRAY)                             \
        ENTITY_NAME##_INDEPENDENT_MEMBERS(SERIALIZE_BINARY_FIELD)                              \
        ENTITY_NAME##_STD_CONTAINERS(SERIALIZE_BINARY_FIELD)                                   \
        ENTITY_NAME##_RUNTIME_ARRAYS(SAVE_BINARY_RUNTIME_ARRAY)                                \
    }                                                                                          \
                                                                                               \
    template <class Archive> void load(Archive &archive)                                       \
    {                                                                                          \
        BASE_DATABASE_INDEPENDENT_MEMBERS(SERIALIZE_BINARY_FIELD)                           \
        BASE_DATABASE_RUNTIME_ARRAYS(LOAD_BINARY_RUNTIME_ARRAY)                             \
        ENTITY_NAME##_INDEPENDENT_MEMBERS(SERIALIZE_BINARY_FIELD)                              \
        ENTITY_NAME##_STD_CONTAINERS(SERIALIZE_BINARY_FIELD)                                   \
        ENTITY_NAME##_RUNTIME_ARRAYS(LOAD_BINARY_RUNTIME_ARRAY)                                \
    }

#define BASE_DATABASE_CONSTRUCTOR(Entity_name, ENTITY_NAME)                                     \
	Entity_name##Database(Arena *arena, size_t capacity)                                       \
{                                                                                          \
BASE_DATABASE_RUNTIME_ARRAYS(INIT_ARRAY) \
ENTITY_NAME##_RUNTIME_ARRAYS(INIT_ARRAY) \
}

#define CORE_DATABASE_CREATION(Entity_name, entity_name, ENTITY_NAME) \
BASE_DATABASE_DECLARATION(ENTITY_NAME) \
BASE_DATABASE_CONSTRUCTOR(Entity_name, ENTITY_NAME) \
BASE_STRUCT_SERIALIZATION(ENTITY_NAME)

#define BASE_DATABASE_CREATION(Entity_name, entity_name, ENTITY_NAME) \
CORE_DATABASE_CREATION(Entity_name, entity_name, ENTITY_NAME) \
BASE_ENTITY_SPAWN(Entity_name, entity_name, ENTITY_NAME##_RUNTIME_ARRAYS) \
BASE_ENTITY_DELETE()

#define POSITIONAL_DATABASE_CREATION(Entity_name, entity_name, ENTITY_NAME) \
CORE_DATABASE_CREATION(Entity_name, entity_name, ENTITY_NAME) \
POSITIONAL_ENTITY_SPAWN(Entity_name, entity_name, ENTITY_NAME##_RUNTIME_ARRAYS) \
BASE_ENTITY_DELETE()

#define MOVABLE_DATABASE_CREATION(Entity_name, entity_name, ENTITY_NAME) \
