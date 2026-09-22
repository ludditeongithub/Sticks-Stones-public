#pragma once
#include <core/tables.hpp>
#include <display/ui/aggregates/info_box.hpp>
#include "enum.hpp"

namespace knowledge {
inline const RaggedLookupTable<Academic, Academic> ACADEMIC_PREREQUISITES = []
{
	using enum Academic;
	RaggedLookupTable<Academic, Academic> lt{};

	return lt;
}();

inline constexpr LookupTable<Academic, Technology> ACADEMIC_TECHNOLOGY_BOOSTS = []
{
	LookupTable<Academic, Technology> lt{};
	using enum Academic;

	return lt;
}();

inline constexpr LookupTable<Academic, const char*> ACADEMIC_DESCRIPTIONS = []
{
	LookupTable<Academic, const char*> lt{};
	using enum Academic;

	return lt;
}();

  inline constexpr LookupTable<Technology,const char*> TECHNOLOGY_DESCRIPTIONS = [] {
    LookupTable<Technology, const char*> lt{};
    using enum Technology;
    
    return lt;
  }();
}

