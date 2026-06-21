#pragma once

#define DECLARE_ARRAY(type, name, ...) \
    Array<type> name;

#define INIT_ARRAY(type, name, ...) \
    name = arena_make_array<type>(arena, capacity);
         
#define DECLARE_MEMBER(type, name) \
     type name;

