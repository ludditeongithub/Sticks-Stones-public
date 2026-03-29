#include <cassert>
#include <cstdint>
#include <array>
#include <iostream>


template<typename... Enums>
struct ConcatEnum {
    using underlying = uint32_t;
    static constexpr std::size_t count = sizeof...(Enums);

    static constexpr std::array<underlying, count> sizes = {
        static_cast<underlying>(Enums::MAX)...
    };

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
        for (auto s : sizes)
            total += s;
        return total;
    }();

    template<typename E>
    static constexpr underlying cast(E e) {
        constexpr std::size_t i = index_of<E>();
        return offsets[i] + static_cast<underlying>(e);
    }

    static constexpr auto cast(underlying idx) {
    for (std::size_t i = 0; i < count; ++i) {
        if (idx < offsets[i] + sizes[i]) {
            return std::pair{i, idx - offsets[i]};
        }
    }
    return std::pair{0u, 0u};
    }


private:
    template<typename T, std::size_t I = 0>
    static consteval std::size_t index_of() {
	    using types = std::tuple<Enums...>;
	    if (I >= sizeof...(Enums))
	    {
		    // TODO: throw
		    std::cout << "Tried to pass value that was larger than total concat enum size." << std::endl;
	    } else if constexpr (std::is_same_v<T, std::tuple_element_t<I, types>>) {
            return I;
        } else {
            return index_of<T, I + 1>();
        }
    }
};
