#pragma once

#include <cstdint>
#include <tuple>
#include <type_traits>

template<typename Enum, unsigned Bits>
struct EnumField
{
    using enum_type = Enum;
    static constexpr unsigned bits = Bits;

    static_assert(std::is_enum_v<Enum>);
};

template<typename T>
constexpr T bitmask(unsigned bits)
{
    constexpr unsigned width = sizeof(T) * 8;

    if (bits >= width)
        return ~T{0};

    return (T{1} << bits) - 1;
}

template<unsigned Bits>
using smallest_uint_t =
    std::conditional_t<
        Bits <= 8,
        uint8_t,
        std::conditional_t<
            Bits <= 16,
            uint16_t,
            std::conditional_t<
                Bits <= 32,
                uint32_t,
                uint64_t>>>;

template<typename... Fs>
class PackedEnum
{
private:
    static constexpr unsigned total_bits = (Fs::bits + ... + 0);

    static_assert(total_bits <= 64);

public:
    using Storage = smallest_uint_t<total_bits>;

    Storage raw{};

private:
    template<typename Enum>
    static consteval unsigned bits_of()
    {
        unsigned result = 0;
        bool found = false;

        (
            [&]
            {
                if constexpr (std::is_same_v<Enum, typename Fs::enum_type>)
                {
                    result = Fs::bits;
                    found = true;
                }
            }(),
            ...
        );

        //static_assert(found, "Enum not present in PackedEnum");

        return result;
    }

    template<typename Enum>
    static consteval unsigned offset_of()
    {
        constexpr auto fields = std::tuple<Fs...>{};

        unsigned offset = 0;
        bool found = false;

        [&]<std::size_t... I>(std::index_sequence<I...>)
        {
            (
                [&]
                {
                    using F = std::tuple_element_t<I, decltype(fields)>;

                    if constexpr (std::is_same_v<Enum, typename F::enum_type>)
                    {
                        for (std::size_t j = I + 1; j < sizeof...(Fs); ++j)
                        {
                            offset += []<std::size_t K>()
                            {
                                using G = std::tuple_element_t<K, decltype(fields)>;
                                return G::bits;
                            }.template operator()<j>();
                        }

                        found = true;
                    }
                }(),
                ...
            );
        }(std::make_index_sequence<sizeof...(Fs)>{});

        // static_assert(found, "Enum not present in PackedEnum");

        return offset;
    }

    template<typename Enum>
    static constexpr unsigned field_bits = bits_of<Enum>();

    template<typename Enum>
    static constexpr unsigned field_offset = []{
        unsigned result = 0;
        bool found = false;

        auto process = [&]<typename F>()
        {
            if (!found)
            {
                if constexpr (std::is_same_v<Enum, typename F::enum_type>)
                {
                    found = true;
                }
                else
                {
                    result += F::bits;
                }
            }
        };

        (process.template operator()<Fs>(), ...);

        return total_bits - result - field_bits<Enum>;
    }();

    template<typename Enum>
    static constexpr Storage field_mask =
        bitmask<Storage>(field_bits<Enum>)
        << field_offset<Enum>;

public:
    constexpr PackedEnum() = default;

    constexpr PackedEnum(typename Fs::enum_type... values)
    {
        (set<typename Fs::enum_type>(values), ...);
    }

    template<typename Enum>
    constexpr Enum get() const
    {
        using U = std::underlying_type_t<Enum>;

        return static_cast<Enum>(
            static_cast<U>(
                (raw & field_mask<Enum>) >>
                field_offset<Enum>));
    }

    template<typename Enum>
    constexpr void set(Enum value)
    {
        using U = std::underlying_type_t<Enum>;

        Storage v = static_cast<Storage>(
            static_cast<U>(value));

        raw =
            (raw & ~field_mask<Enum>) |
            ((v << field_offset<Enum>) &
             field_mask<Enum>);
    }
};
