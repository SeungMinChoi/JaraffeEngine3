#include "JFAllocator.h"

#include <new>

void* JFFoundation::JFAllocator::Alloc(size_t s)
{
	return malloc(s);//Allocator()->Alloc(s);
}

void* JFFoundation::JFAllocator::ReAlloc(void* p, size_t s)
{
	return realloc(p, s);//Allocator()->ReAlloc(p, s);
}

void JFFoundation::JFAllocator::Free(void* p)
{
	free(p);//Allocator()->Free(p);
}

JFFoundation::JFAllocator& JFFoundation::JFAllocator::DefaultAllocator()
{
	static JFFoundation::JFAllocator allocator;
	return allocator;
}

JFFoundation::JFAllocator::JFAllocator(void)
{
}

JF_API void* operator new(size_t s, JFFoundation::JFAllocator& alloactor)
{
	return alloactor.Alloc(s);
}

JF_API void operator delete(void* p, JFFoundation::JFAllocator& allocator)
{
	allocator.Free(p);
}
