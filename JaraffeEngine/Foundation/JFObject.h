#pragma once

namespace JFFoundation
{
	// TODO :ref count 만들어야함
	template <typename T>
	class JFObject
	{
	public:
		JFObject(const T* p = nullptr)
			: target(p)
		{}
		JFObject(const JFObject& obj)
			: target(obj.target)
		{}
		JFObject(JFObject&& obj) noexcept
			: target(nullptr)
		{
			target = obj.target;
			obj.target = nullptr;
		}

		~JFObject(void)
		{}

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
			target = obj;
			return *this;
		}
		JFObject& operator = (const JFObject& obj)
		{
			target = obj.target;
		}
		JFObject& operator = (JFObject&& obj) noexcept
		{
			target = obj.target;
			obj.target = nullptr;
			return *this;
		}

	private:
		T* target;
	};
}