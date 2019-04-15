#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
	namespace JFAlgorithm
	{
		template <class Value>
		struct JFDefaultLessComparator
		{
			FORCEINLINE bool operator () (const Value& lhs, const Value& rhs) const
			{
				return lhs < rhs;
			}
		};

		template <>
		struct JFDefaultLessComparator<void>
		{
			template <class Value>
			FORCEINLINE bool operator () (const Value& lhs, const Value& rhs) const
			{
				return lhs < rhs;
			}
		};

		template <class Value>
		struct JFDefaultLessComparator<Value*>
		{
			FORCEINLINE bool operator () (const Value* lhs, const Value* rhs) const
			{
				return (*lhs) < (*rhs);
			}
		};

		template <class T>
		FORCEINLINE void Swap(T& lhs, T& rhs)
		{
			T temp(std::move(lhs));
			lhs = std::move(rhs);
			rhs = std::move(temp);
		}

		template <class Value, class Comparator>
		FORCEINLINE void Sort3(Value& min, Value& mid, Value& max, Comparator& comparator)
		{
			if (!comparator(mid, min))
			{
				if (!comparator(max, mid))
					return;

				Swap(mid, max);

				if (comparator(mid, min))
					Swap(min, mid);

				return;
			}
			if (comparator(max, mid))
			{
				Swap(min, max);
				return;
			}
			Swap(min, mid);
			if (comparator(max, mid))
			{
				Swap(mid, max);
			}
		}

		template <class Iterator, class Comparator>
		void InsertionSort(Iterator first, Iterator end, Comparator& comparator)
		{
			Iterator i = first + 1;
			for (; i != end; ++i)
			{
				Iterator j = i;

				auto t(std::move(*j));
				for (Iterator k = i; k != first && comparator(t, *--k); --j)
					*j = std::move(*k);
				*j = std::move(t);
			}
		}

		template <class Iterator, class Comparator>
		void Sort(Iterator first, Iterator end, Comparator comparator)
		{
			while (true)
			{
				auto count = end - first;

				switch (count)
				{
				case 0:
				case 1:
					return;
				case 2:
					if (comparator(*(first + 1), *first))
						Swap(*first, *(first + 1));
					return;
				case 3:
					Sort3(*first, *(first + 1), *(first + 2), comparator);
					return;
				}

				if (count < 16)
				{
					InsertionSort(first, end, comparator);
					return;
				}

				// midian 3
				Iterator min = first;
				Iterator mid = first + (count >> 1);
				Iterator max = end - 1;
				Sort3(*min, *mid, *max, comparator);

				// setting pivot position
				Iterator pivot = max;
				Swap(*pivot, *mid);

				// pass compara to sorted value
				++min;
				--max;

				// split partition
				while (true)
				{
					while (comparator(*min, *pivot))
						++min;

					while (comparator(*pivot, *max))
						--max;

					if (min >= max)
						break;

					Swap(*min, *max);

					++min;
					--max;
				}

				// new pivot position
				Swap(*min, *pivot);
				pivot = min;

				// small range to tail recursion
				if ((pivot - first) < (end - pivot))
				{
					Sort(first, pivot, comparator);
					first = pivot + 1;
				}
				else
				{
					Sort(pivot + 1, end, comparator);
					end = pivot;
				}
			}
		}

		template <class Iterator, class Comparator = JFDefaultLessComparator<void>>
		void Sort(Iterator first, Iterator end)
		{
			Sort(first, end, Comparator());
		}
	}
}