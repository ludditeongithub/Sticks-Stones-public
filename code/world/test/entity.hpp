#pragma once
#include <core/data.hpp>
#include <vector>
#include <core/containers.hpp>
#include <macros/constructors.hpp>
#include <macros/database.hpp>

enum class Butt
{
		fat,
		skinny
};
struct ButtDatabase {
#define BUTT_INDEPENDENT_MEMBERS(X) X(int, butt)

#define BUTT_RUNTIME_ARRAYS(X) X(int, face, 0, 4) \
		X(Butt, nick, Butt::fat, Butt::skinny)
       
#define BUTT_STD_CONTAINERS(X) 
		// DEFAULT_DATABASE_INDEPENDENT_MEMBERS(DECLARE_MEMBER);                          
		// DEFAULT_DATABASE_RUNTIME_ARRAYS(DECLARE_ARRAY);
		// BUTT_INDEPENDENT_MEMBERS(DECLARE_MEMBER);
		// BUTT_RUNTIME_ARRAYS(DECLARE_ARRAY);

		DEFAULT_DATABASE_CREATION(Butt, butt, BUTT);
};



