#pragma once

namespace JFFoundation
{
	class JFRefCounter
	{
	public:
		JFRefCounter()
			: count(1)
		{}

		void AddRef()
		{
			++count;
		}

		int Release()
		{
			assert(count > 0);
			return --count;
		}

		int GetCount()
		{
			return count;
		}

	private:
		int count;
	};
}