#pragma once
#include <cassert>
#include "memory.hpp"

template <typename T>
struct Array {
    T* data = nullptr;
    uint32_t count = 0;
    uint32_t capacity = 0;

    Array(uint32_t capacity) {
      this->capacity = capacity;
    }

    void reserve(uint32_t newCapacity) {
        if (newCapacity <= capacity) return;

        T* newData = static_cast<T*>(
            operator new[](sizeof(T) * newCapacity)
        );

        for (uint32_t i = 0; i < count; ++i)
            new (&newData[i]) T(std::move(data[i]));

        for (uint32_t i = 0; i < count; ++i)
            data[i].~T();

        operator delete[](data);

        data = newData;
        capacity = newCapacity;
    }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        if (count == capacity) {
            reserve(capacity ? capacity * 2 : 16);
        }

        T* obj = new (&data[count]) T(std::forward<Args>(args)...);
        ++count;
        return *obj;
    }

    void pop_back() {
        data[--count].~T();
    }

    void clear() {
        for (uint32_t i = 0; i < count; ++i)
            data[i].~T();
        count = 0;
    }

    T& operator[](uint32_t i) {
        return data[i];
    }

    const T& operator[](uint32_t i) const {
        return data[i];
    }

    uint32_t size() const {
        return count;
    }

    ~Array() {
        clear();
        operator delete[](data);
    }
};

template <typename T>
struct PriorityQueue {
  Arena<T> arena; 
  int current;
  int nx;

  inline T top() {
    return arena[current];
  };
  
  inline void pop() {
    if (current > arena.capacity) std::cerr << "Priority Queue is out of memory!" << std::endl;
    current++;
  };

  inline T next() {
    return arena[nx++];
  };

  inline void resetNext() {
    nx = current;
  };
};

