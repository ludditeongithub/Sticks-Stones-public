#pragma once
#include <cstdlib>
#include <array>
#include <unordered_map>
#include <bitset>

template<typename Enum, typename T, std::size_t N = static_cast<std::size_t>(Enum::MAX)>
struct LookupTable {
    std::array<T, N> data{};

    constexpr T& operator[](Enum e) {
        return data[static_cast<std::size_t>(e)];
    }

    constexpr const T& operator[](Enum e) const {
        return data[static_cast<std::size_t>(e)];
    }
};

template<typename T, std::size_t Cols>
struct Row : std::array<T, Cols> {
    constexpr Row& operator=(std::initializer_list<T> values) {
        size_t i = 0;
        for (auto v : values) {
            if (i >= Cols) break;
            (*this)[i++] = v;
        }
        return *this;
    }
};

template<typename Enum, typename T, std::size_t Rows = static_cast<size_t>(Enum::MAX), std::size_t Cols = 5>
struct LookupTable2D {
    using RowType = Row<T,Cols>;
    std::array<RowType, Rows> data{};

    constexpr RowType& operator[](Enum e) { return data[static_cast<size_t>(e)]; }
    constexpr const RowType& operator[](Enum e) const { return data[static_cast<size_t>(e)]; }
};

template <typename Enum, std::size_t N = static_cast<std::size_t>(Enum::MAX)>
struct BitsetTable {
    std::bitset<N> b{};

    constexpr auto operator[](Enum e) {
        return b[static_cast<std::size_t>(e)];
    }

    constexpr auto operator[](Enum e) const {
        return b[static_cast<std::size_t>(e)];
    }  

    constexpr BitsetTable& operator|=(const BitsetTable& o) {
        b |= o.b;
        return *this;
    }

  

      struct iterator {
        const std::bitset<N>* bits;
        std::size_t index;

        constexpr iterator(const std::bitset<N>* b, std::size_t i)
            : bits(b), index(i)
        {
            while (index < N && !bits->test(index)) ++index;
        }

        constexpr Enum operator*() const {
            return static_cast<Enum>(index);
        }

        constexpr iterator& operator++() {
            do { ++index; } while (index < N && !bits->test(index));
            return *this;
        }

        constexpr bool operator==(const iterator& other) const {
            return index == other.index;
        }
    };

    constexpr iterator begin() const { return iterator(&b, 0); }
    constexpr iterator end()   const { return iterator(&b, N); }
};
