#pragma once
#include "memory.hpp"
#include <cassert>
#include <cereal/archives/binary.hpp>
#include <stdexcept>
#include <typeinfo>

// right now is really ArrayChunk,which points to next ArrayChunk if applicable
// TODO: make separate LinkedArray which is really ArrayChunk,

template <typename T>
struct Array
{
    Arena* arena;
    size_t size;    
    size_t capacity;

    T* data;

    T& operator[](size_t index)
    {
        if (index >= capacity)
            throw std::out_of_range("capacity overflow");

        if (index >= size)
            size = index + 1;

        return data[index];
    }

    const T& operator[](size_t index) const
    {
        if (index >= size)
            throw std::out_of_range("reading uninitialized element");

        return data[index];
    }

    bool is_full() const
    {
        return size == capacity;
    }

    uint16_t size_bytes() const
    {
        return sizeof(Array<T>) + sizeof(T) * capacity;
    }

    const std::type_info& type() const
    {
        return typeid(T);
    }

    template<class Archive>
    void save(Archive& ar) const
    {
        ar(capacity, size);

        for (size_t i = 0; i < size; i++)
            ar(data[i]);
    }

    template<class Archive>
    void load(Archive& ar)
    {
        ar(capacity, size);

        data = static_cast<T*>(
            arena_alloc(*arena, sizeof(T) * capacity)
        );

        for (uint16_t i = 0; i < size; i++)
            ar(data[i]);
    }
};

template <typename T>
Array<T>& arena_make_array(Arena& arena, size_t capacity)
{
    void* mem = arena_alloc_aligned(
        arena,
        sizeof(Array<T>),
        alignof(Array<T>)
    );

    Array<T>* arr = new (mem) Array<T>();

    arr->arena = arena;
    arr->capacity = capacity;
    arr->size = 0;

    arr->data = static_cast<T*>(
        arena_alloc(arena, sizeof(T) * capacity)
    );

    return *arr;
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
Array2D<T>& arena_make_2d_array(Arena& arena,
                                uint16_t width,
                                uint16_t height)
{
  size_t total_elements = static_cast<size_t>(width * height);

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

	inline void reset_next() { nx = current; };
};

template<typename T>
struct Stack
{
    Array<T>* array;

    bool empty() const
    {
        return array->size == 0;
    }

    uint16_t size() const
    {
        return array->size;
    }

    void push(const T& value)
    {
        if (array->size >= array->capacity)
            throw std::out_of_range("stack overflow");

        array->data[array->size++] = value;
    }

    void pop()
    {
        if (array->size == 0)
            throw std::out_of_range("stack underflow");

        --array->size;
    }

    T& top()
    {
        if (array->size == 0)
            throw std::out_of_range("empty stack");

        return array->data[array->size - 1];
    }

    const T& top() const
    {
        if (array->size == 0)
            throw std::out_of_range("empty stack");

        return array->data[array->size - 1];
    }

    void clear()
    {
        array->size = 0;
    }
};

/*
template <typename T, typename P = uint8_t, typename I = uint16_t> struct PriorityQueue
{
		std::vector<std::pair<T, P>> data;
		I capacity;
		I size = 0;
		I top_index = 0;
		I end_index = 0;
		I current = 0;

		PriorityQueue<T>(I capacity) : capacity(capacity)
		{

		}

		T top()
		{
				return data[top_index];
		}
		void pop()
		{
				top_index++;
				size--;
		}

		inline I get_middle(I first, I end) {
			if (end > capacity)
					{
							end = (first + size - capacity);
							I range = capacity - first + end;
							I half_range = range / 2;
							if (half_range > end)
							{
									middle = first + half_range;
							} else middle = end - half_range;
					} else middle = (end - first) / 2;
			return middle;
		}

		void push(T item, P priority)
		{
			// binary search
			I middle;
			I end = end_index;
			I previous;

			bool found = false;
			while (!found) {
					if (priority <= data[middle].second()) 	          	{
					if (middle == 0) I previous = capacity;
					else I previous = middle - 1;
						if (priority >= data[previous].second()) {
								found = true;
								insert(item, priority, middle);
						}
						last = middle;
						middle = get_middle(first, last);
					} else {
					if (middle == capacity) I next = 0;
					else I next = middle + 1;
						if (priority <= data[next].second()) {
								found = true;
								insert(item, priority, middle);
						}
						first = middle;
						middle = get_middle(first, last);
					}
			}
		}

		void insert(T item, P priority, I index) {
				if (size++ >= capacity) {
					data.push_back(data[capacity]);
				}
					for (size_t i = capacity; i > 0; i--) {
							if (i == index) {
									data[i] = {item, priority};
									break;
							}
							data[i] = data[i-1];
					}
					if (index < top_index - 1) top_index++;
		}


		T next()
		{
				return data[++current];
		}
		void snapback()
		{
				current = top_index;
		}
		bool empty() { return size = 0; }
		bool next_empty() { return ((end_index > top_index && current + 1 >= end_index) ||
(end_index < top_index && (current + 1 =< top_index && current + 1 >= end_index))); }
};
*/

template<typename T>
Stack<T> arena_make_stack(Arena* arena, uint16_t capacity)
{
    Stack<T> stack;

    stack.array = &arena_make_array<T>(arena, capacity);

    return stack;
}
