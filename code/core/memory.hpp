#pragma once
#include <cstdint>
#include <iostream>
#include <new>
#include <type_traits>
#include <tuple>
#include <vector>


template <typename T>
struct Arena {
    const uint32_t capacity;
    T* start;
    uint32_t used;

    Arena(uint32_t cap)
        : capacity(cap),
          start(new T[cap]{}),
          used(0)
    {}

    ~Arena() {
        delete[] start;
    }

    T* alloc() {
        if (used >= capacity) {
            std::cerr << "Arena is out of memory!" << std::endl;
            return nullptr;
        }
        return &start[used++];
    }

    T& operator[](size_t index) {
        if (index >= used) {
            throw std::out_of_range("Arena index out of range");
        }
        return start[index];
    }

    const T& operator[](size_t index) const {
        if (index >= used) {
            throw std::out_of_range("Arena index out of range");
        }
        return start[index];
    }


    T* begin() { return start; }
    T* end() { return start + used; }
    const T* begin() const { return start; }
    const T* end() const { return start + used; }

    void reset() { used = 0; }
    uint32_t size() const { return used; }
    uint32_t remaining() const { return capacity - used; }
};

template <typename T>
struct Pool {
    T* data;
    uint32_t* freeList;
    uint32_t capacity;
    uint32_t freeHead;

    Pool(uint32_t cap)
        : capacity(cap), freeHead(0)
    {
        data = static_cast<T*>(operator new[](sizeof(T) * capacity));
        freeList = new uint32_t[capacity];
        for (uint32_t i = 0; i < capacity; ++i)
            freeList[i] = i;
    }

    ~Pool() {
        operator delete[](data);
        delete[] freeList;
    }

    T* alloc() {
        if (freeHead >= capacity)
            return nullptr;
        uint32_t index = freeList[freeHead++];
        return new (&data[index]) T();
    }

    void dealloc(T* obj) {
        if (!obj) return;
        uint32_t index = static_cast<uint32_t>(obj - data);
        obj->~T();
        freeList[--freeHead] = index;
    }
};
