#pragma once
#include <../extern/magic_enum/magic_enum.hpp>
#include <stdexcept>

template<typename A, typename B>
B reflectEnum(A a) {
auto name = magic_enum::enum_name(a);

auto b_opt = magic_enum::enum_cast<B>(name);

if (!b_opt) {
    throw std::runtime_error("Invalid enum mapping");
}

return *b_opt;		
}
