#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
	class JF_API JFAllocator
	{
	public:
		void* Alloc(size_t);
		void* ReAlloc(void*, size_t);
		void Free(void*);

		static JFAllocator& DefaultAllocator();

	private:
		JFAllocator(void);
		JFAllocator(const JFAllocator&) = delete;
		JFAllocator& operator = (const JFAllocator&) = delete;
	};

	struct JFDefaultAllocator
	{
		static void* Alloc(size_t s) { return JFAllocator::DefaultAllocator().Alloc(s); }
		static void* Realloc(void* p, size_t s) { return JFAllocator::DefaultAllocator().ReAlloc(p, s); }
		static void Free(void* p) { JFAllocator::DefaultAllocator().Free(p); }
	};
}

JF_API void* operator new (size_t, JFFoundation::JFAllocator&);
JF_API void operator delete (void*, JFFoundation::JFAllocator&);