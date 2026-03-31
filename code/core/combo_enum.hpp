#pragma once
#include <cassert>
#include <cstdint>
#include <array>
#include <iostream>
#include <variant>
#include <tuple>
#include <utility>

template<typename... Enums>
struct ConcatEnum {
    using underlying = uint32_t;
    static constexpr std::size_t count = sizeof...(Enums);

    // sizes of each enum
    static constexpr std::array<underlying, count> sizes = { static_cast<underlying>(Enums::MAX)... };

    static constexpr std::array<underlying, count> offsets = [] {
        std::array<underlying, count> arr{};
        underlying sum = 0;
        for (std::size_t i = 0; i < count; ++i) {
            arr[i] = sum;
            sum += sizes[i];
        }
        return arr;
    }();

    static constexpr underlying MAX = [] {
        underlying total = 0;
        for (auto s : sizes) total += s;
        return total;
    }();

    // map a single enum to underlying index
    template<typename E>
    static constexpr underlying cast(E e) {
        constexpr std::size_t i = index_of<E>();
        return offsets[i] + static_cast<underlying>(e);
    }

    template<typename F, std::size_t I = 0>
    static constexpr void cast_impl(underlying idx, F&& f) {
        if constexpr (I < count) {
            if (idx < offsets[I] + sizes[I]) {
                using E = std::tuple_element_t<I, std::tuple<Enums...>>;
                f(static_cast<E>(idx - offsets[I])); 
            } else {
                cast_impl<I + 1>(idx, std::forward<F>(f));
            }
        } else {
            throw std::out_of_range("Index out of bounds in ConcatEnum::cast_impl");
        }
    }

    template<typename F>
    static constexpr void cast(underlying idx, F&& f) {
        cast_impl(idx, std::forward<F>(f));
    }

private:
    template<typename T, std::size_t I = 0>
    static consteval std::size_t index_of() {
        using types = std::tuple<Enums...>;
        if constexpr (I >= sizeof...(Enums)) {
            static_assert(I < sizeof...(Enums), "Type not found in ConcatEnum");
            return 0;
        } else if constexpr (std::is_same_v<T, std::tuple_element_t<I, types>>) {
            return I;
        } else {
            return index_of<T, I + 1>();
        }
    }
};
