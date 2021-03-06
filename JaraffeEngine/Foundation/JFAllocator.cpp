#include "JFAllocator.h"
#include "JFScopeLock.h"
#include "JFSpinLock.h"

#include <new>
#include <stdint.h>
#include <cmath>

class Chunk;
class Unit;

namespace Private
{
	class CustomHeap
	{
		enum { InitialHeapSize = 1 << 25 };

	public:
		CustomHeap()
		{
			heap = ::HeapCreate(0, InitialHeapSize, 0);
		}
		~CustomHeap()
		{
			HeapDestroy(heap);
		}

		void* Alloc(size_t size)
		{
			return HeapAlloc(heap, 0, size);
		}

		static CustomHeap* Instance()
		{
			static CustomHeap customHeap;
			return &customHeap;
		}

	private:
		HANDLE heap;
	};
}

struct Unit
{
	Chunk* chunk;
	Unit* prevUnit;
	Unit* nextUnit;

	void* Data()
	{
		uint8_t* address = (uint8_t*)this;
		return address + sizeof(Chunk*) + sizeof(Unit*) + sizeof(Unit*);
	}
};

class Chunk
{
public:
	void Init(int unitSize, int unitCount)
	{
		this->unitSize = unitSize;
		this->unitCount = unitCount;

		size_t pysicalUnitSize = unitSize + (sizeof(Unit));
		uint8_t* memoryBuffer = (uint8_t*)Private::CustomHeap::Instance()->Alloc(unitCount * pysicalUnitSize);
		for (int i = 0; i < unitCount; ++i)
		{
			Unit* newUnit = new (memoryBuffer + (i * pysicalUnitSize)) Unit();
			newUnit->chunk = this;

			if (freeUnitChain)
			{
				newUnit->prevUnit = freeUnitChain;
				freeUnitChain->nextUnit = newUnit;
			}
			freeUnitChain = newUnit;
		}
	}

	void* Alloc(size_t s)
	{
		if (!freeUnitChain)
		{
			if (!nextChunk)
			{
				nextChunk = (Chunk*)Private::CustomHeap::Instance()->Alloc(sizeof(Chunk));
				nextChunk->Init(unitSize, unitCount);
			}

			return nextChunk->Alloc(s);
		}

		Unit* unit = freeUnitChain;
		freeUnitChain = freeUnitChain->prevUnit;

		if (usedUnitChain)
		{
			unit->prevUnit = usedUnitChain;
			usedUnitChain->nextUnit = unit;
		}
		usedUnitChain = unit;

		return unit->Data();
	}

	void Free(Unit* unit)
	{
		if (unit->prevUnit)
		{
			unit->prevUnit->nextUnit = unit->nextUnit;
		}
		if (unit->nextUnit)
		{
			unit->nextUnit->prevUnit = unit->prevUnit;
		}

		if (unit->chunk->freeUnitChain)
		{
			unit->prevUnit = unit->chunk->freeUnitChain;
			unit->chunk->freeUnitChain->nextUnit = unit;
		}
		unit->chunk->freeUnitChain = unit;
	}

private:
	int unitSize;
	int unitCount;

	Chunk* nextChunk = nullptr;
	Unit* freeUnitChain = nullptr;
	Unit* usedUnitChain = nullptr;
};

class JFMemoryPool
{
	enum {
		InitUnitMemory = 1 << 16,
		MaxUnitSize = 1 << 15,		// 32KB
		AlignmentUnitSize = 16,
		NumChunk = MaxUnitSize / AlignmentUnitSize
	};
	
public:
	void Init()
	{
		for (int i = 0; i < NumChunk; ++i)
		{
			chunks[i].Init((i+1) * AlignmentUnitSize, InitUnitMemory / ((i+1) * AlignmentUnitSize));
		}
	}

	void* Alloc(size_t s)
	{
		JFFoundation::JFScopeLock<JFFoundation::JFSpinLock> lock(lock);

		// TODO:
		if (s > MaxUnitSize)
			assert(false);

		return chunks[int(ceil(s / 16))].Alloc(s);
	}

	void* ReAlloc(void* p, size_t s)
	{
		JFFoundation::JFScopeLock<JFFoundation::JFSpinLock> lock(lock);

		// TODO
		return nullptr;
	}

	void Free(void* p)
	{
		JFFoundation::JFScopeLock<JFFoundation::JFSpinLock> lock(lock);

		uint8_t* address = (uint8_t*)p;
		Unit* unit = (Unit*)(address - sizeof(Unit));
		unit->chunk->Free(unit);
	}

private:
	JFFoundation::JFSpinLock lock;
	Chunk chunks[NumChunk];
};

static JFMemoryPool memoryPool;

void* JFFoundation::JFAllocator::Alloc(size_t s)
{
	return memoryPool.Alloc(s);
}

void* JFFoundation::JFAllocator::ReAlloc(void* p, size_t s)
{
	return memoryPool.ReAlloc(p, s);
}

void JFFoundation::JFAllocator::Free(void* p)
{
	memoryPool.Free(p);
}

JFFoundation::JFAllocator& JFFoundation::JFAllocator::DefaultAllocator()
{
	static JFFoundation::JFAllocator allocator;
	return allocator;
}

JFFoundation::JFAllocator::JFAllocator(void)
{
	Init();
}

JFFoundation::JFAllocator::~JFAllocator()
{
}

void JFFoundation::JFAllocator::Init()
{
	memoryPool.Init();
}
