// Хренов Геннадий
// Аллокатор
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "vector.h"
#include <cstdlib>

template <class T, size_t BLOCK_SIZE>
class Allocator {
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using size_type = std::size_t;

	Allocator() noexcept : Buffer(nullptr), FreeBl(0)
	{
		static_assert(BLOCK_SIZE > 0, "Block size is lower then 0");
	}

	~Allocator() noexcept
	{
		free(Buffer);
	}

	template <class U>
	struct rebind {
		using other = Allocator<U, BLOCK_SIZE>;
	};

	T* allocate(size_t n)
	{
		if (!Buffer) {
			Buffer = (T*)malloc(BLOCK_SIZE * sizeof(T));
			FreeBl.Resize(BLOCK_SIZE);
			FreeBlocksFill();
		}

		int i = SearchFreeSpace(n);
		FreeBl.Erase(FreeBl.begin() + i - n + 1, FreeBl.begin() + i + 1);
		return Buffer + i;
	}

	void deallocate(T* ptr, size_t n)
	{
		for (int i = 0; i < n; ++i) {
			FreeBl.PushBack(ptr + i);
		}
	}

	template <typename U, typename ...Args>
	void construct(U* p, Args&& ...args) {
		new (p) U(std::forward<Args>(args)...);
	}

	void destroy(pointer p) {
		p->~T();
	}


private:
	T* Buffer;
	vector<T*> FreeBl;

	void FreeBlocksFill()
	{
		for (int i = 0; i < BLOCK_SIZE; ++i) {
			FreeBl[i] = Buffer + i;
		}
	}

	int SearchFreeSpace(size_t n)
	{
		size_t total = 0;

		int i = FreeBl.Size() - 1;
		for (; i >= 0; --i) {
			total = 1;
			for (int j = i; j > 0 && total < n; --j) {
				if (FreeBl[j] - FreeBl[j - 1] == 1)
					++total;
			}
			if (total >= n)
				break;
		}

		if (total < n)
			throw std::bad_alloc();

		return i;
	}
};

#endif