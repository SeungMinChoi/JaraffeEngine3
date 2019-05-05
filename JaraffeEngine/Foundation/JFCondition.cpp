#include "JFCondition.h"

namespace Private
{
	// <condition_variable>
	// Event안쓰는 이유 : 락은 건애가 풀어야 하는대 이놈은 안그럼
	// https://docs.microsoft.com/en-us/windows/desktop/sync/condition-variables
	// https://docs.microsoft.com/en-us/windows/desktop/sync/using-condition-variables
	class JFConditionImpl
	{
	public:
		JFConditionImpl()
		{
			InitializeConditionVariable(&condition);
			InitializeCriticalSectionAndSpinCount(&criticalSection, 1024);
		}

		~JFConditionImpl()
		{
			DeleteCriticalSection(&criticalSection);
		}

		void Lock()
		{
			EnterCriticalSection(&criticalSection);
		}

		bool TryLock()
		{
			return TryEnterCriticalSection(&criticalSection);
		}

		void Unlock()
		{
			LeaveCriticalSection(&criticalSection);
		}

		void Sleep(JFFoundation::JFCondition::MilliSecond wait)
		{
			SleepConditionVariableCS(&condition, &criticalSection, wait);
		}

		void Wake()
		{
			WakeConditionVariable(&condition);
		}

		void WakeAll()
		{
			WakeAllConditionVariable(&condition);
		}

	private:
		CONDITION_VARIABLE condition;
		CRITICAL_SECTION criticalSection;
	};
}

JFFoundation::JFCondition::JFCondition()
{
	impl = new Private::JFConditionImpl();
}

JFFoundation::JFCondition::~JFCondition()
{
	if (impl)
	{
		delete impl;
		impl = nullptr;
	}
}

JFFoundation::JFCondition::JFCondition(JFCondition&& cond) noexcept
{
	impl = cond.impl;
	cond.impl = nullptr;
}

JFFoundation::JFCondition& JFFoundation::JFCondition::operator=(JFCondition&& cond) noexcept
{
	impl = cond.impl;
	cond.impl = nullptr;
	return *this;
}

void JFFoundation::JFCondition::Lock()
{
	reinterpret_cast<Private::JFConditionImpl*>(impl)->Lock();
}

bool JFFoundation::JFCondition::TryLock()
{
	return reinterpret_cast<Private::JFConditionImpl*>(impl)->TryLock();
}

void JFFoundation::JFCondition::Unlock()
{
	reinterpret_cast<Private::JFConditionImpl*>(impl)->Unlock();
}

void JFFoundation::JFCondition::Sleep(MilliSecond wait)
{
	reinterpret_cast<Private::JFConditionImpl*>(impl)->Sleep(wait);
}

void JFFoundation::JFCondition::Wake()
{
	reinterpret_cast<Private::JFConditionImpl*>(impl)->Wake();
}

void JFFoundation::JFCondition::WakeAll()
{
	reinterpret_cast<Private::JFConditionImpl*>(impl)->WakeAll();
}