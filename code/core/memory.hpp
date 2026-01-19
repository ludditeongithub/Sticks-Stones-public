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
struct Arena2D {
    Arena<T>& arena;
    uint32_t rows;
    uint32_t cols;

    struct RowProxy {
        T* row_start;
        T& operator[](uint32_t col) {
            return row_start[col];
        }
        const T& operator[](uint32_t col) const {
            return row_start[col];
        }
    };

    Arena2D(Arena<T>& a, uint32_t r, uint32_t c)
        : arena(a), rows(r), cols(c) {
        if (r * c > a.capacity) {
            throw std::runtime_error("Arena too small for requested 2D view");
        }
    }

  Arena2D(uint32_t r, uint32_t c) : rows(r), cols(c) {
      arena = new Arena<T>(r * c);      
    }
      

    RowProxy operator[](uint32_t row) {
        if (row >= rows) throw std::out_of_range("Row out of range");
        return RowProxy{arena.start + row * cols};
    }

    const RowProxy operator[](uint32_t row) const {
        if (row >= rows) throw std::out_of_range("Row out of range");
        return RowProxy{arena.start + row * cols};
    }

    uint32_t size() const { return rows * cols; }
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

template <typename T>
struct Buffer {
  T *data;
  uint32_t size;

   T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Arena index out of range");
        }
        return data[index];
    }  

     const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Arena index out of range");
        }
        return data[index];
     }
  
};  
