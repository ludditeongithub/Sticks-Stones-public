#pragma once
#include <cstdint>
#include <new>
#include <stdexcept>

struct Arena
{
    char* start;
    size_t capacity;
    size_t used;

    explicit Arena(size_t cap)
        : capacity(cap), used(0)
    {
        start = static_cast<char*>(
            ::operator new(cap, std::align_val_t(64))
        );
    }

    ~Arena()
    {
        ::operator delete(start, std::align_val_t(64));
    }

    void reset()
    {
        used = 0;
    }
};

void* arena_alloc(Arena& arena, size_t bytes)
{
    if (arena.used + bytes > arena.capacity)
        throw std::bad_alloc();

    void* ptr = arena.start + arena.used;
    arena.used += bytes;
    return ptr;
}

void* arena_alloc_aligned(Arena& arena,
                          size_t bytes,
                          size_t alignment)
{
    uintptr_t current =
        reinterpret_cast<uintptr_t>(arena.start + arena.used);

    uintptr_t aligned =
        (current + alignment - 1) & ~(alignment - 1);

    size_t padding = aligned - current;

    if (arena.used + padding + bytes > arena.capacity)
        throw std::bad_alloc();

    arena.used += padding;

    void* ptr = arena.start + arena.used;
    arena.used += bytes;

    return ptr;
}

template <typename T> struct Pool
{
	T *data;
	uint32_t *freeList;
	uint32_t capacity;
	uint32_t freeHead;

	Pool(uint32_t cap) : capacity(cap), freeHead(0)
	{
		data = static_cast<T *>(operator new[](sizeof(T) * capacity));
		freeList = new uint32_t[capacity];
		for (uint32_t i = 0; i < capacity; ++i)
			freeList[i] = i;
	}

	~Pool()
	{
		operator delete[](data);
		delete[] freeList;
	}

	T *alloc()
	{
		if (freeHead >= capacity)
			return nullptr;
		uint32_t index = freeList[freeHead++];
		return new (&data[index]) T();
	}

	void dealloc(T *obj)
	{
		if (!obj)
			return;
		uint32_t index = static_cast<uint32_t>(obj - data);
		obj->~T();
		freeList[--freeHead] = index;
	}
};

template <typename T> struct Buffer
{
	T *data;
	uint32_t size;

	T &operator[](uint16_t index)
	{
		if (index >= size)
		{
			throw std::out_of_range("Arena index out of range");
		}
		return data[index];
	}

	const T &operator[](uint16_t index) const
	{
		if (index >= size)
		{
			throw std::out_of_range("Arena index out of range");
		}
		return data[index];
	}
};
