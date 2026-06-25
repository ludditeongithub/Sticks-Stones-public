#pragma once
#include <array>
#include <bitset>
#include <cstdint>
#include <array>
#include <cassert>
#include <utility>

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

template <typename Enum, typename T, size_t N, size_t MAX = Enum::MAX>
struct RaggedLookupTable {
	std::array<T, N> data;
	std::array<size_t, MAX> offsets{};
	// uint16_t current = 0; //current relies on RaggedTable being initialized correctly (all of the same Enum being done at once), and only once, as it increments over the lambda initalization.
	// Enum type;
	// //TODO: safety checking with dynamic boolean table during intialization
	
	// constexpr uint32_t size()
	// {
	// 	return N;
	// }		

	constexpr size_t size(Enum e) const
	{
		return offsets[static_cast<int>(e) + 1] - offsets[static_cast<int>(e)];
	}		

	constexpr T get(Enum e, size_t index) const
	{
		uint32_t offset = offsets[static_cast<int>(e)];
		assert(index < offsets[static_cast<int>(e) + 1] - offset);
		return data[offset + index];
	}
	
	template<typename Container>
	constexpr void set(Enum e, const Container& value)
	{
		uint32_t offset = offsets[static_cast<int>(e)];
		//TODO: sort role enums and turn on assert
		//assert(!(static_cast<int>(e) != 0 && offset == 0));
		for (size_t i = 0; i < value.size(); i++) data[offset + i] = value[i];
		offsets[static_cast<int>(e)] = offset + value.size();
        }		
};
