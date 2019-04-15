#pragma once

namespace JFFoundation
{
	template<typename ITEMREF>
	class JFIterator
	{
	public:
		JFIterator(ITEMREF* item)
			: currentItem(item)
		{
		}

		bool operator != (const JFIterator& it) const
		{
			return this->currentItem != it.currentItem;
		}

		JFIterator& operator ++ ()
		{
			++currentItem;
			return *this;
		}

		ITEMREF& operator * ()
		{
			return *currentItem;
		}
	private:
		ITEMREF* currentItem;
	};
}