#pragma once
#include <cstdint>

template <typename E1, unsigned B1, typename E2, unsigned B2>
struct PackedEnum2 {
    static_assert(B1 + B2 <= 8);

    uint8_t raw{};

    constexpr PackedEnum2(E1 e1, E2 e2)
        : raw((uint8_t(e1) << B2) | uint8_t(e2)) {}

private:
    static constexpr uint8_t mask2 = (1u << B2) - 1;
    static constexpr uint8_t mask1 = ((1u << B1) - 1) << B2;

public:
    struct FirstProxy {
        PackedEnum2& parent;

        constexpr operator E1() const {
            return E1(parent.raw >> B2);
        }

        constexpr FirstProxy& operator=(E1 value) {
            parent.raw = (parent.raw & ~mask1)
                       | (uint8_t(value) << B2);
            return *this;
        }
    };

    struct SecondProxy {
        PackedEnum2& parent;

        constexpr operator E2() const {
            return E2(parent.raw & mask2);
        }

        constexpr SecondProxy& operator=(E2 value) {
            parent.raw = (parent.raw & ~mask2)
                       | uint8_t(value);
            return *this;
        }
    };

    constexpr FirstProxy first() { return FirstProxy{*this}; }
    constexpr SecondProxy second() { return SecondProxy{*this}; }

    constexpr E1 first() const {
        return E1(raw >> B2);
    }

    constexpr E2 second() const {
        return E2(raw & mask2);
    }
};


template <typename E1, unsigned B1,
          typename E2, unsigned B2,
          typename E3, unsigned B3>
struct PackedEnum3 {
    static_assert(B1 + B2 + B3 <= 8);

    uint8_t raw{};

    constexpr PackedEnum3(E1 e1, E2 e2, E3 e3)
        : raw((uint8_t(e1) << (B2 + B3)) |
              (uint8_t(e2) << B3) |
               uint8_t(e3)) {}

private:
    static constexpr uint8_t mask1 = ((1u << B1) - 1) << (B2 + B3);
    static constexpr uint8_t mask2 = ((1u << B2) - 1) << B3;
    static constexpr uint8_t mask3 = (1u << B3) - 1;

public:
    struct FirstProxy {
        PackedEnum3& p;

        constexpr operator E1() const {
            return E1((p.raw & mask1) >> (B2 + B3));
        }

        constexpr FirstProxy& operator=(E1 value) {
            p.raw = (p.raw & ~mask1)
                  | ((uint8_t(value) << (B2 + B3)) & mask1);
            return *this;
        }
    };

    struct SecondProxy {
        PackedEnum3& p;

        constexpr operator E2() const {
            return E2((p.raw & mask2) >> B3);
        }

        constexpr SecondProxy& operator=(E2 value) {
            p.raw = (p.raw & ~mask2)
                  | ((uint8_t(value) << B3) & mask2);
            return *this;
        }
    };

    struct ThirdProxy {
        PackedEnum3& p;

        constexpr operator E3() const {
            return E3(p.raw & mask3);
        }

        constexpr ThirdProxy& operator=(E3 value) {
            p.raw = (p.raw & ~mask3)
                  | (uint8_t(value) & mask3);
            return *this;
        }
    };

    constexpr FirstProxy  first()  { return {*this}; }
    constexpr SecondProxy second() { return {*this}; }
    constexpr ThirdProxy  third()  { return {*this}; }

    constexpr E1 first()  const { return E1((raw & mask1) >> (B2 + B3)); }
    constexpr E2 second() const { return E2((raw & mask2) >> B3); }
    constexpr E3 third()  const { return E3(raw & mask3); }
};


template <typename E1, unsigned B1,
          typename E2, unsigned B2,
          typename E3, unsigned B3>
struct PackedEnum3_16 {
    static_assert(B1 + B2 + B3 <= 16);

    uint16_t raw{};

    constexpr PackedEnum3_16(E1 e1, E2 e2, E3 e3)
        : raw((uint16_t(e1) << (B2 + B3)) |
              (uint16_t(e2) << B3) |
               uint16_t(e3)) {}

private:
    static constexpr uint16_t mask1 =
        ((uint16_t(1) << B1) - 1) << (B2 + B3);
    static constexpr uint16_t mask2 =
        ((uint16_t(1) << B2) - 1) << B3;
    static constexpr uint16_t mask3 =
        (uint16_t(1) << B3) - 1;

public:
    struct FirstProxy {
        PackedEnum3_16& p;

        constexpr operator E1() const {
            return E1((p.raw & mask1) >> (B2 + B3));
        }

        constexpr FirstProxy& operator=(E1 value) {
            p.raw = (p.raw & ~mask1)
                  | ((uint16_t(value) << (B2 + B3)) & mask1);
            return *this;
        }
    };

    struct SecondProxy {
        PackedEnum3_16& p;

        constexpr operator E2() const {
            return E2((p.raw & mask2) >> B3);
        }

        constexpr SecondProxy& operator=(E2 value) {
            p.raw = (p.raw & ~mask2)
                  | ((uint16_t(value) << B3) & mask2);
            return *this;
        }
    };

    struct ThirdProxy {
        PackedEnum3_16& p;

        constexpr operator E3() const {
            return E3(p.raw & mask3);
        }

        constexpr ThirdProxy& operator=(E3 value) {
            p.raw = (p.raw & ~mask3)
                  | (uint16_t(value) & mask3);
            return *this;
        }
    };

    constexpr FirstProxy  first()  { return {*this}; }
    constexpr SecondProxy second() { return {*this}; }
    constexpr ThirdProxy  third()  { return {*this}; }

    constexpr E1 first()  const { return E1((raw & mask1) >> (B2 + B3)); }
    constexpr E2 second() const { return E2((raw & mask2) >> B3); }
    constexpr E3 third()  const { return E3(raw & mask3); }
};


template <typename E1, unsigned B1,
          typename E2, unsigned B2,
          typename E3, unsigned B3,
          typename E4, unsigned B4>
struct PackedEnum4_32 {
    static_assert(B1 + B2 + B3 + B4 <= 32);

    uint32_t raw{};

    constexpr PackedEnum4_32(E1 e1, E2 e2, E3 e3, E4 e4)
        : raw((uint32_t(e1) << (B2 + B3 + B4)) |
              (uint32_t(e2) << (B3 + B4)) |
              (uint32_t(e3) << B4) |
               uint32_t(e4)) {}

private:
    static constexpr unsigned S1 = B2 + B3 + B4;
    static constexpr unsigned S2 = B3 + B4;
    static constexpr unsigned S3 = B4;

    static constexpr uint32_t M1 =
        ((uint32_t(1) << B1) - 1) << S1;
    static constexpr uint32_t M2 =
        ((uint32_t(1) << B2) - 1) << S2;
    static constexpr uint32_t M3 =
        ((uint32_t(1) << B3) - 1) << S3;
    static constexpr uint32_t M4 =
        (uint32_t(1) << B4) - 1;

public:
    struct FirstProxy {
        PackedEnum4_32& p;
        constexpr operator E1() const {
            return E1((p.raw & M1) >> S1);
        }
        constexpr FirstProxy& operator=(E1 value) {
            p.raw = (p.raw & ~M1)
                  | ((uint32_t(value) << S1) & M1);
            return *this;
        }
    };

    struct SecondProxy {
        PackedEnum4_32& p;
        constexpr operator E2() const {
            return E2((p.raw & M2) >> S2);
        }
        constexpr SecondProxy& operator=(E2 value) {
            p.raw = (p.raw & ~M2)
                  | ((uint32_t(value) << S2) & M2);
            return *this;
        }
    };

    struct ThirdProxy {
        PackedEnum4_32& p;
        constexpr operator E3() const {
            return E3((p.raw & M3) >> S3);
        }
        constexpr ThirdProxy& operator=(E3 value) {
            p.raw = (p.raw & ~M3)
                  | ((uint32_t(value) << S3) & M3);
            return *this;
        }
    };

    struct FourthProxy {
        PackedEnum4_32& p;
        constexpr operator E4() const {
            return E4(p.raw & M4);
        }
        constexpr FourthProxy& operator=(E4 value) {
            p.raw = (p.raw & ~M4)
                  | (uint32_t(value) & M4);
            return *this;
        }
    };

    constexpr FirstProxy  first()  { return {*this}; }
    constexpr SecondProxy second() { return {*this}; }
    constexpr ThirdProxy  third()  { return {*this}; }
    constexpr FourthProxy fourth() { return {*this}; }

    constexpr E1 first()  const { return E1((raw & M1) >> S1); }
    constexpr E2 second() const { return E2((raw & M2) >> S2); }
    constexpr E3 third()  const { return E3((raw & M3) >> S3); }
    constexpr E4 fourth() const { return E4(raw & M4); }
};
