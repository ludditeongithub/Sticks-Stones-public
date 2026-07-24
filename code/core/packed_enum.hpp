#pragma once
#include <cstdint>
#include <tuple>
#include <type_traits>
#include <utility>

template<typename T, unsigned Bits>
struct Field
{
    using value_type = T;
    static constexpr unsigned BITS = Bits;

    static_assert(std::is_enum_v<T> ||
                  (std::is_integral_v<T> && std::is_unsigned_v<T>));
};

template<typename T>
using field_value_type =
    std::conditional_t<
        std::is_enum_v<T>,
        std::underlying_type_t<T>,
        T>;

template<typename T>
constexpr T bitmask(unsigned bits)
{
    constexpr unsigned WIDTH = sizeof(T) * 8;

    if (bits >= WIDTH)
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
    static constexpr unsigned TOTAL_BITS = (Fs::BITS + ... + 0);
    static_assert(TOTAL_BITS <= 64);

public:
    using Storage = smallest_uint_t<TOTAL_BITS>;
    Storage raw{};

    template<typename T>
    static consteval unsigned bits_of()
    {
        unsigned result = 0;

        (
            [&]
            {
                if constexpr (std::is_same_v<T, typename Fs::value_type>)
                    result = Fs::BITS;
            }(),
            ...
        );

        return result;
    }

    template<typename T>
    static constexpr unsigned FIELD_BITS = bits_of<T>();

    template<typename T>
    static constexpr unsigned FIELD_OFFSET = [] {
        unsigned offset = 0;
        bool found = false;

        auto process = [&]<typename F>()
        {
            if (!found)
            {
                if constexpr (std::is_same_v<T, typename F::value_type>)
                {
                    found = true;
                }
                else
                {
                    offset += F::BITS;
                }
            }
        };

        (process.template operator()<Fs>(), ...);

        return offset;
    }();

    template<typename T>
    static constexpr Storage FIELD_MASK =
        bitmask<Storage>(FIELD_BITS<T>) << FIELD_OFFSET<T>;

    constexpr PackedEnum() = default;

    constexpr PackedEnum(typename Fs::value_type... values)
    {
        (set<typename Fs::value_type>(values), ...);
    }

    template<typename T>
    constexpr T get() const
    {
        using U = field_value_type<T>;

        return static_cast<T>(
            static_cast<U>(
                (raw & FIELD_MASK<T>) >> FIELD_OFFSET<T>));
    }

    template<typename T>
    constexpr void set(T value)
    {
        using U = field_value_type<T>;

        Storage v = static_cast<Storage>(static_cast<U>(value));

        raw =
            (raw & ~FIELD_MASK<T>) |
            ((v << FIELD_OFFSET<T>) & FIELD_MASK<T>);
    }
};
