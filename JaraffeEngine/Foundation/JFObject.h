#pragma once

#include "JFRefCounter.h"

namespace JFFoundation
{
	// TODO :ref count 만들어야함
	template <typename T>
	class JFObject
	{
	public:
		JFObject(T* p = nullptr)
			: target(p)
			, refCounter(new JFRefCounter)
		{}
		JFObject(const JFObject& obj)
			: target(obj.target)
			, refCounter(obj.refCounter)
		{
			refCounter->AddRef();
		}
		JFObject(JFObject&& obj) noexcept
			: target(obj.target)
			, refCounter(obj.refCounter)
		{
			obj.target = nullptr;
			obj.refCounter = nullptr;
		}

		~JFObject(void)
		{
			Release();
		}

		T* operator -> (void)
		{
			return target;
		}
		const T* operator -> (void) const
		{
			return target;
		}

		T* operator * (void)
		{
			return *target;
		}
		const T* operator * (void) const
		{
			return *target;
		}

		JFObject& operator = (const T* obj)
		{
			if (target != obj)
			{
				Release();
				refCounter = new JFRefCounter();
			}

			target = obj;
			return *this;
		}
		JFObject& operator = (const JFObject& obj)
		{
			if(target != obj.target)
				Release();

			target = obj.target;
			refCounter = obj.refCounter;
		}
		JFObject& operator = (JFObject&& obj) noexcept
		{
			if(target != obj.target)
				Release();

			target = obj.target;
			refCounter = obj.refCounter;

			obj.target = nullptr;
			obj.refCounter = nullptr;
			
			return *this;
		}

	private:
		void Release()
		{
			if (refCounter->Release() == 0)
			{
				assert(target);
				assert(refCounter);

				delete target;
				delete refCounter;
			}
		}

		T* target;
		JFRefCounter* refCounter;
	};
}