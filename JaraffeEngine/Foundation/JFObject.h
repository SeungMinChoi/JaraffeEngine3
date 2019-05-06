#pragma once

#include "../JFInclude.h"
#include "JFRefCounter.h"

namespace JFFoundation
{
	// TODO :ref count 만들어야함
	template <typename T>
	class JF_API JFObject
	{
	public:
		JFObject(T* p = nullptr)
			: target(p)
			, refCounter(nullptr)
		{
			AddRef();
		}
		JFObject(const JFObject& obj)
			: target(obj.target)
			, refCounter(obj.refCounter)
		{
			AddRef();
		}
		JFObject(JFObject&& obj) noexcept
			: target(obj.target)
			, refCounter(obj.refCounter)
		{
			obj.target = nullptr;
			obj.refCounter = nullptr;
		}

		~JFObject() noexcept
		{
			Release();
		}

		T* operator -> ()
		{
			return target;
		}
		const T* operator -> () const
		{
			return target;
		}

		T* operator * ()
		{
			return target;
		}
		const T* operator * () const
		{
			return target;
		}

		operator T* ()
		{
			return target;
		}
		operator const T* () const
		{
			return target;
		}

		// JFObject Type인대 target만 넘긴다면 문제됨.
		JFObject& operator = (T* obj)
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
			AddRef();
			
			return *this;
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
		void AddRef()
		{
			if (target == nullptr)
				return;

			if (refCounter == nullptr)
				refCounter = new JFRefCounter;

			refCounter->AddRef();
		}

		void Release()
		{
			if (refCounter->Release() == 0)
			{
				assert(target);
				assert(refCounter);

				// 이 부분을 따로 빼야함. ( 전방선언이 안먹힘 )
				delete target;
				delete refCounter;

				target = nullptr;
				refCounter = nullptr;
			}
		}

		T* target;
		JFRefCounter* refCounter;
	};
}