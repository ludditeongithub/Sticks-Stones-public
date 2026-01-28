#pragma once
#include <cstdint>

template <typename E1, unsigned B1, typename E2, unsigned B2>
struct PackedEnum2 {
    static_assert(B1 + B2 <= 8);

    uint8_t raw{};

    constexpr PackedEnum2(E1 e1, E2 e2)
        : raw((uint8_t(e1) << B2) | uint8_t(e2)) {}

    constexpr E1 first() const {
        return E1(raw >> B2);
    }

    constexpr E2 second() const {
        return E2(raw & ((1u << B2) - 1));
    }
};

template <typename E1, unsigned B1, typename E2, unsigned B2, typename E3, unsigned B3>
struct PackedEnum3 {
    static_assert(B1 + B2 + B3 <= 8);

    uint8_t raw{};

  constexpr PackedEnum3(E1 e1, E2 e2, E3 e3)
    : raw(uint8_t(e1) << (B2 + B3) | (uint8_t(e2) << B3) | uint8_t(e3)) {}

  constexpr E1 first() const {
    return E1((raw >> (B2 + B3)) & ((1u << B1) - 1));
  }

  constexpr E2 second() const {
    return E2((raw >> B3) & ((1u << B2) - 1));
  }

  constexpr E3 third() const {
    return E3(raw & ((1u << B3) - 1));
  }
};
