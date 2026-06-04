#pragma once
#include <cassert>
#include <cstdint>
#include <array>
#include <variant>
#include <tuple>

template<typename... Enums>
struct ConcatEnum {
    using underlying = uint32_t;
    static constexpr std::size_t count = sizeof...(Enums);

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

    template<typename E>
    static constexpr underlying cast(E e) {
        constexpr std::size_t i = index_of<E>();
        return offsets[i] + static_cast<underlying>(e);
    }

    using Variant = std::variant<Enums...>;

    template<std::size_t I = 0>
    static constexpr Variant cast(underlying idx) {
        if constexpr (I < count) {
            if (idx < offsets[I] + sizes[I]) {
                using E = std::tuple_element_t<I, std::tuple<Enums...>>;
                return Variant{static_cast<E>(idx - offsets[I])};
            } else {
                return cast<I + 1>(idx);
            }
        } else {
            throw std::out_of_range("Index out of bounds in ConcatEnum::cast");
        }
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
