#pragma once
#include <array>
#include <bitset>
#include <cstdint>

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

template <typename Enum, typename T, uint16_t Rows = static_cast<uint16_t>(Enum::MAX),
	  uint16_t Cols = 5>
struct LookupTable2D
{
	using RowType = Row<T, Cols>;
	std::array<RowType, Rows> data{};

	constexpr RowType &operator[](Enum e) { return data[static_cast<uint16_t>(e)]; }
	constexpr const RowType &operator[](Enum e) const { return data[static_cast<uint16_t>(e)]; }
};

template <typename Enum, uint16_t N = static_cast<uint16_t>(Enum::MAX)> struct BitsetTable
{
	std::bitset<N> b{};

	constexpr auto operator[](Enum e) { return b[static_cast<uint16_t>(e)]; }

	constexpr auto operator[](Enum e) const { return b[static_cast<uint16_t>(e)]; }

	constexpr BitsetTable &operator|=(const BitsetTable &o)
	{
		b |= o.b;
		return *this;
	}

	constexpr void set(Enum e) { b[e] = true; }

	struct iterator
	{
		const std::bitset<N> *bits;
		uint16_t index;

		constexpr iterator(const std::bitset<N> *b, uint16_t i) : bits(b), index(i)
		{
			while (index < N && !bits->test(index))
				++index;
		}

		constexpr Enum operator*() const { return static_cast<Enum>(index); }

		constexpr iterator &operator++()
		{
			do
			{
				++index;
			} while (index < N && !bits->test(index));
			return *this;
		}

		constexpr bool operator==(const iterator &other) const
		{
			return index == other.index;
		}
	};

	constexpr iterator begin() const { return iterator(&b, 0); }
	constexpr iterator end() const { return iterator(&b, N); }
};
