#pragma once

#include <memory>

#include "JFMath.h"
#include "JFIterator.h"
#include "JFAllocator.h"

namespace JFFoundation
{
	template<class VALUE, class ALLOCATOR = JFDefaultAllocator>
	class JFArray
	{
	public:
		using Iterator = JFIterator<VALUE>;
		using ConstIterator = JFIterator<const VALUE>;

		Iterator begin() { return Iterator(&data[0]); }
		ConstIterator begin() const { return ConstIterator(&data[0]); }
		Iterator end() { return Iterator(&data[count]); }
		ConstIterator end() const { return ConstIterator(&data[count]); }

		JFArray()
			: data(nullptr)
			, count(0)
			, capacity(0)
		{}

		JFArray(size_t c, const VALUE& v = VALUE())
			: JFArray()
		{
			Add(c, v);
		}

		JFArray(const JFArray& lhs)
			: JFArray()
		{
			Reserve(lhs.capacity);

			memcpy_s(data, sizeof(VALUE) * capacity, lhs.data, sizeof(VALUE) * lhs.capacity);
			count = lhs.count;
		}

		JFArray(JFArray&& rhs) noexcept
			: JFArray()
		{
			data = rhs.data;
			count = rhs.count;
			capacity = rhs.capacity;

			rhs.data = nullptr;
			rhs.count = 0;
			rhs.capacity = 0;
		}

		JFArray(std::initializer_list<VALUE> l)
			: JFArray()
		{
			Reserve(l.size());
			for (auto& v : l)
			{
				Add(v);
			}
		}

		~JFArray()
		{
			if (data) 
				ALLOCATOR::Free(data);

			data = nullptr;
			count = 0;
			capacity = 0;
		}

		size_t Add(const VALUE& v)
		{
			_AddSize(1);
			new(std::addressof(data[count])) VALUE(v);
			return count++;
		}

		size_t Add(VALUE&& v) noexcept
		{
			_AddSize(1);
			new(std::addressof(data[count])) VALUE(std::move(v));
			return count++;
		}

		size_t Add(size_t s, const VALUE& v)
		{
			_AddSize(s);
			for (size_t i = 0; i < s; ++i)
				new(std::addressof(data[count++])) VALUE(v);
			return count;
		}

		void Reserve(size_t s)
		{
			if (s <= capacity)
				return;

			if (data)
				data = static_cast<VALUE*>(ALLOCATOR::Realloc(data, sizeof(VALUE) * s));
			else
				data = static_cast<VALUE*>(ALLOCATOR::Alloc(sizeof(VALUE) * s));

			capacity = s;
		}

		void Resize(size_t s)
		{
			if (count < s)
			{
				Reserve(s);

				for (size_t i = count; i < s; ++i)
					new(std::addressof(data[count++])) VALUE();
			}
			else
			{
				for (size_t i = s; i < count; ++i)
					data[i].~VALUE();

				count = s;
			}
		}

		void ShrinkToFit()
		{
			if (capacity <= 0 || count == capacity)
				return;

			if (count == 0 && data)
			{
				ALLOCATOR::Free(data);
			}
			else
			{
				for (size_t i = count; i < capacity; ++i)
					data[i].~VALUE();

				data = static_cast<VALUE*>(ALLOCATOR::Realloc(data, sizeof(VALUE) * count));
			}
			
			capacity = count;
		}

		void Clear()
		{
			for (size_t i = 0; i < count; ++i)
				data[i].~VALUE();
			count = 0;
		}

		size_t Count()
		{
			return count;
		}

		VALUE* Data()
		{
			return data;
		}

		const VALUE* Data() const
		{
			return data;
		}

		VALUE& operator [](size_t index) const
		{
			return data[index];
		}
	
	private:
		void _AddSize(size_t s)
		{
			if (capacity >= (count + s))
				return;

			const size_t CalculatedCapacity = capacity + Max(capacity >> 1, 1);
			Reserve(CalculatedCapacity);
		}

		VALUE* data;
		size_t count;
		size_t capacity;
	};
}