#pragma once
#include <array>
#include <bitset>
#include <cstdint>
#include <cassert>
#include <utility>
#include <vector>
#include <span>

template <typename Enum, typename T, uint16_t N = static_cast<uint16_t>(Enum::MAX)>
struct LookupTable
{
	std::array<T, N> data{};

	constexpr T &operator[](Enum e) { return data[static_cast<uint16_t>(e)]; }

	constexpr const T &operator[](Enum e) const { return data[static_cast<uint16_t>(e)]; }
};

template <typename T, uint16_t Cols> struct Row : std::array<T, Cols>
{
	constexpr Row &operator=(std::initializer_list<T> values)
	{
		uint16_t i = 0;
		for (auto v : values)
		{
			if (i >= Cols)
				break;
			(*this)[i++] = v;
		}
		return *this;
	}
};

template <typename T, uint16_t Cols, typename ColEnum>
struct LookupRow
{
    std::array<T, Cols> data{};

    constexpr T& operator[](ColEnum col)
    {
        return data[static_cast<uint16_t>(col)];
    }

    constexpr const T& operator[](ColEnum col) const
    {
        return data[static_cast<uint16_t>(col)];
    }
};

template <
    typename RowEnum,
    typename ColEnum,
    typename T,
    uint16_t Rows = static_cast<uint16_t>(RowEnum::MAX),
    uint16_t Cols = static_cast<uint16_t>(ColEnum::MAX)>
struct LookupTable2D
{
    using Row = LookupRow<T, Cols, ColEnum>;

    std::array<Row, Rows> data{};

    constexpr Row& operator[](RowEnum row)
    {
        return data[static_cast<uint16_t>(row)];
    }

    constexpr const Row& operator[](RowEnum row) const
    {
        return data[static_cast<uint16_t>(row)];
    }
};

template <typename Enum, uint16_t N = static_cast<uint16_t>(Enum::MAX)>
struct BitsetTable
{
	std::bitset<N> bitset{};

	constexpr bool operator[](Enum e) const
	{
		return bitset.test(static_cast<uint16_t>(e));
	}

	constexpr void set(Enum e, bool value = true)
	{
		bitset.set(static_cast<uint16_t>(e), value);
	}

	constexpr void reset(Enum e)
	{
		bitset.reset(static_cast<uint16_t>(e));
	}

	constexpr BitsetTable& operator|=(const BitsetTable& o)
	{
		bitset |= o.bitset;
		return *this;
	}

	constexpr BitsetTable& operator&=(const BitsetTable& o)
	{
		bitset &= o.bitset;
		return *this;
	}

	constexpr BitsetTable operator|(const BitsetTable& o) const
	{
		BitsetTable tmp = *this;
		tmp |= o;
		return tmp;
	}

	constexpr BitsetTable operator&(const BitsetTable& o) const
	{
		BitsetTable tmp = *this;
		tmp &= o;
		return tmp;
	}
};

template<typename Enum, typename T>
struct RaggedLookupTable
{
    std::vector<T> data;
    std::array<std::pair<size_t, size_t>, static_cast<size_t>(Enum::MAX) + 1> ranges{};

    void set(Enum e, std::initializer_list<T> list)
    {
        size_t start = data.size();

        data.insert(data.end(), list.begin(), list.end());

        ranges[static_cast<size_t>(e)] = {
            start,
            data.size()
        };
    }

    std::span<const T> get(Enum e) const
    {
        auto [start, end] = ranges[static_cast<size_t>(e)];
        return std::span<const T>(data.data() + start, end - start);
    }
};
