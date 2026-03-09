#pragma once
#include <cassert>
#include <stdexcept>
#include "memory.hpp"


//right now is really ArrayChunk,which points to next ArrayChunk if applicable
//TODO: make separate LinkedArray which is really ArrayChunk, 
template <typename T>
struct Array {
    uint16_t count;
    uint16_t capacity;
    Array* next = nullptr;

    // Returns pointer to the data buffer after the chunk metadata
    T* data() { return reinterpret_cast<T*>(this + 1); }
    const T *data() const { return reinterpret_cast<const T *>(this + 1); }      

    bool is_full() const { return count == capacity; }

    bool push(const T& value) {
        if (is_full()) return false;
        data()[count++] = value;
        return true;
    }

    bool push(T&& value) {
        if (is_full()) return false;
        data()[count++] = std::move(value);
        return true;
    }
   
    uint16_t size() { //in bytes 
      return sizeof(Array<T>) + sizeof(T) * capacity;
    }    
  
    T& operator[](uint16_t index) {
        if (index >= count)
            throw std::out_of_range("Tried to access index outside of current Array size");
        return data()[index];
    }

    const T& operator[](uint16_t index) const {
        if (index >= count)
            throw std::out_of_range("Tried to access index outside of current Array size");
        return data()[index];
    }
};

template <typename T>
Array<T>* arena_make_array(Arena* arena, uint16_t capacity) {
    uint16_t bytes = sizeof(Array<T>) + sizeof(T) * capacity;

    void* mem = arena_alloc_aligned(
        arena,
        bytes,
        alignof(Array<T>)
    );

    Array<T>* arr = new (mem) Array<T>();
    arr->count = 0;
    arr->capacity = capacity;
    arr->next = nullptr;

    return arr;
}

// pq capacity remains the same size, since as current moves away from start, if the end of the memory of this structure is full, then new values are pushed onto the front of the memory of this structure, where their actual position is the relative wraparound positon from cur
template <typename T> struct Queue {
  uint16_t start;   //where the memory starts
  uint16_t current; // where the current queue starts/top
  uint16_t nx;
  uint16_t end; //last filled value of the current queue
  uint16_t capacity;

      // Returns pointer to the data buffer after the chunk metadata
    T* data() { return reinterpret_cast<T*>(this + 1); }
    const T *data() const { return reinterpret_cast<const T *>(this + 1); }      

  inline T top() {
    return data()[current];
  };

  inline void pop() {
    current++;
    if (current > start + capacity)
      current = start;
  };

  inline bool push(T* value) {
    if (end + 1 == start) throw std::out_of_range("Tried to fill queue index larger than capacity.");
    else data()[end++] = value;
  }

  inline T next() {
    if (nx == start + capacity) nx = start;
    return data()[nx++];
  };

  inline void resetNext() { nx = current; };  
};

