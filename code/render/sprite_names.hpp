#pragma once
#include <cstdio>
#include <type_traits>
#include <variant>
#include <world/buildable/enum.hpp>
#include <world/animal/enum.hpp>
#include <world/item/enum.hpp>
#include <world/plant/enum.hpp>
#include <core/tables.hpp>
#include <magic_enum/magic_enum.hpp>
#include <magic_enum/magic_enum_utility.hpp>
#include <string>

namespace sprite {

std::string to_kebab_case(std::string& s) {
    std::string result;

    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];

        if (std::isupper(static_cast<unsigned char>(c))) {
            if (i > 0) result += '-';
            result += std::tolower(static_cast<unsigned char>(c));
        } else {
            result += c;
        }
    }

    return result;
}

template<typename S>
std::string get_sprite_name(S sprite_type)
{
    std::string name = std::string(magic_enum::enum_name(sprite_type));

    if constexpr (std::is_same_v<S, Plant>)
    {
        if (Item item = magic_enum::enum_cast<Item>(name); item.has_value())
        {
            name += "-plant";
        }
    }
    return to_kebab_case(name) + ".aseprite";
}

};
