#pragma once
#include "memory.hpp"
#include <extern/nameof.hpp>
#include <cassert>
#include <extern/cereal/archives/binary.hpp>
#include <stdexcept>

// right now is really ArrayChunk,which points to next ArrayChunk if applicable
// TODO: make separate LinkedArray which is really ArrayChunk,
template <typename T> struct Array
{
	Arena* arena;
	uint16_t count;
	uint16_t capacity;
//	Array *next = nullptr;

	// Returns pointer to the data buffer after the chunk metadata
	T *data() { return reinterpret_cast<T *>(this + 1); }
	const T *data() const { return reinterpret_cast<const T *>(this + 1); }

	bool is_full() const { return count == capacity; }

	void push(const T &value)
	{
		//        if (is_full()) //TODO: error
		data()[count++] = value;
	}

	void push(T &&value)
	{
		//        if (is_full()) //TODO: error
		data()[count++] = std::move(value);
		//        return true;
	}

	uint16_t size()
	{ // in bytes
		return sizeof(Array<T>) + sizeof(T) * capacity;
	}

	T &operator[](uint16_t index)
	{
		if (index >= count)
			throw std::out_of_range(
			    "Tried to access index outside of current Array size");
		return data()[index];
	}

	const T &operator[](uint16_t index) const
	{
		if (index >= count)
			throw std::out_of_range(
			    "Tried to access index outside of current Array size");
		return data()[index];
	}

	// void operator=(uint16_t index) const {
	// 	    if (index >= count)
	//           throw std::out_of_range(
	//               "Tried to access index outside of current Array size");
	// 	    else data()[index] =
	// }

	template <class Archive> void save(Archive &archive, std::string name)
	{
		archive(cereal::binary_data(arena, capacity, count, data()));		
	}

template <class Archive> void load(Arena* arena, Archive &archive)
{
	archive(cereal::binary_data(arena, capacity, count, data()));
	arena_load_array<T>(arena, capacity, count, data());
}	
};

template <typename T> Array<T> &arena_make_array(Arena *arena, uint16_t capacity)
{
	uint16_t bytes = sizeof(Array<T>) + sizeof(T) * capacity;

	void *mem = arena_alloc_aligned(arena, bytes, alignof(Array<T>));

	Array<T> &arr = new (mem) Array<T>();
	arr->count = 0;
	arr->capacity = capacity;
//	arr->next = nullptr;

	return arr;
}

template <typename T> Array<T> &arena_load_array(Arena *arena, uint16_t capacity, uint16_t count, T* data)
{
	uint16_t bytes = sizeof(Array<T>) + sizeof(T) * capacity;

	void *mem = arena_alloc_aligned(arena, bytes, alignof(Array<T>));

	Array<T> &arr = new (mem) Array<T>();
	arr->count = 0;
	arr->capacity = capacity;

	arr[0] = data();
	for (size_t i = 1; i < count; i++) {
		arr.data() = data[i];
	}

	return arr;
}

template <typename T>
struct Array2D
{
    T* data;
    uint16_t width;
    uint16_t height;

    struct Row
    {
        T* row_data;
        uint16_t width;

        T& operator[](uint16_t x)
        {
            if (x >= width)
                throw std::out_of_range("Column index out of bounds");

            return row_data[x];
        }

        const T& operator[](uint16_t x) const
        {
            if (x >= width)
                throw std::out_of_range("Column index out of bounds");

            return row_data[x];
        }
    };

    Row operator[](uint16_t y)
    {
        if (y >= height)
            throw std::out_of_range("Row index out of bounds");

        return Row{ data + y * width, width };
    }

    const Row operator[](uint16_t y) const
    {
        if (y >= height)
            throw std::out_of_range("Row index out of bounds");

        return Row{ data + y * width, width };
    }
};

template <typename T>
Array2D<T>& arena_make_2d_array(Arena* arena,
                                uint16_t width,
                                uint16_t height)
{
    size_t total_elements = static_cast<size_t>(width) * height;

    size_t bytes =
        sizeof(Array2D<T>) +
        sizeof(T) * total_elements;

    void* mem =
        arena_alloc_aligned(arena,
                            bytes,
                            alignof(Array2D<T>));

    // Construct header
    Array2D<T>* arr = new (mem) Array2D<T>();

    // Data lives immediately after header
    T* data = reinterpret_cast<T*>(
        reinterpret_cast<uint8_t*>(mem) + sizeof(Array2D<T>)
    );

    arr->data = data;
    arr->width = width;
    arr->height = height;

    return *arr;
}

// pq capacity remains the same size, since as current moves away from start, if the end of the
// memory of this structure is full, then new values are pushed onto the front of the memory of this
// structure, where their actual position is the relative wraparound positon from cur
template <typename T> struct Queue
{
	uint16_t start;	  // where the memory starts
	uint16_t current; // where the current queue starts/top
	uint16_t nx;
	uint16_t end; // last filled value of the current queue
	uint16_t capacity;

	// Returns pointer to the data buffer after the chunk metadata
	T *data() { return reinterpret_cast<T *>(this + 1); }
	const T *data() const { return reinterpret_cast<const T *>(this + 1); }

	inline T top() { return data()[current]; };

	inline void pop()
	{
		current++;
		if (current > start + capacity)
			current = start;
	};

	inline bool push(T *value)
	{
		if (end + 1 == start)
			throw std::out_of_range("Tried to fill queue index larger than capacity.");
		else
			data()[end++] = value;
	}

	inline T next()
	{
		if (nx == start + capacity)
			nx = start;
		return data()[nx++];
	};

	inline void resetNext() { nx = current; };
};
