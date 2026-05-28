#pragma once
#include <numeric>

template <typename Enum>
inline Enum operator|(Enum a, Enum b)
{
    return static_cast<Enum>(
        static_cast<std::underlying_type_t<Enum>>(a) |
        static_cast<std::underlying_type_t<Enum>>(b));
}

template <typename Enum>
inline Enum &operator|=(Enum &a, Enum b)
{
	a = a | b;
	return a;
}

template <typename Enum>
inline Enum operator&(Enum a, Enum b)
{
	return static_cast<Enum>(
	    static_cast<std::underlying_type_t<Enum>>(a) &
	    static_cast<std::underlying_type_t<Enum>>(b));
}

template <typename Enum>
inline bool hasTag(Enum value, Enum tag)
{
	return static_cast<std::underlying_type_t<Enum>>(value & tag) != 0;
}


