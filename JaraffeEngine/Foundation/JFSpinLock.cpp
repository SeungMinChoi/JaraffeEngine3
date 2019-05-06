#include "JFSpinLock.h"

namespace Private
{
    // https://docs.microsoft.com/en-us/windows/desktop/sync/using-critical-section-objects
    class JFSpinLockImpl
    {
	public:
        JFSpinLockImpl(JFFoundation::JFSpinLock::Count spinCount)
        {
            // Initialize the critical section one time only.
            if (!InitializeCriticalSectionAndSpinCount(&criticalSection, spinCount))
                return;
        }

        ~JFSpinLockImpl() noexcept
        {
            // Release resources used by the critical section object.
            DeleteCriticalSection(&criticalSection);
        }

        void Lock()
        {
            // Request ownership of the critical section.
            EnterCriticalSection(&criticalSection);
        }

        bool TryLock()
        {
            return TryEnterCriticalSection(&criticalSection);
        }

        void Unlock()
        {
            // Release ownership of the critical section.
            LeaveCriticalSection(&criticalSection);
        }

	private:
        CRITICAL_SECTION criticalSection;
    };
}

JFFoundation::JFSpinLock::JFSpinLock(Count spinCount)
{
    impl = new Private::JFSpinLockImpl(spinCount);
}

JFFoundation::JFSpinLock::JFSpinLock(JFSpinLock&& lock) noexcept
{
	impl = lock.impl;
	lock.impl = nullptr;
}

JFFoundation::JFSpinLock::~JFSpinLock() noexcept
{
    if (impl)
    {
        delete impl;
        impl = nullptr;
    }
}

bool JFFoundation::JFSpinLock::TryLock() const
{
	assert(impl);
    return reinterpret_cast<Private::JFSpinLockImpl*>(impl)->TryLock();
}

void JFFoundation::JFSpinLock::Lock() const
{
	assert(impl);
	reinterpret_cast<Private::JFSpinLockImpl*>(impl)->Lock();
}

void JFFoundation::JFSpinLock::Unlock() const
{
	assert(impl);
	reinterpret_cast<Private::JFSpinLockImpl*>(impl)->Unlock();
}
