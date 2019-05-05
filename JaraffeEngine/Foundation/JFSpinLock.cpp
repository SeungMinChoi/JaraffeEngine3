#include "JFSpinLock.h"

namespace Private
{
    // https://docs.microsoft.com/en-us/windows/desktop/sync/using-critical-section-objects
    struct JFSpinLockImpl
    {
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

        CRITICAL_SECTION criticalSection;
    };
}

JFFoundation::JFSpinLock::JFSpinLock(Count spinCount)
{
    impl = new Private::JFSpinLockImpl(spinCount);
}

JFFoundation::JFSpinLock::~JFSpinLock() noexcept
{
    if (impl)
    {
        delete impl;
        impl = nullptr;
    }
}

JFFoundation::JFSpinLock::JFSpinLock(JFSpinLock&& lock) noexcept
{
    impl = lock.impl;
    lock.impl = nullptr;
}

JFFoundation::JFSpinLock& JFFoundation::JFSpinLock::operator=(JFSpinLock&& lock) noexcept
{
    impl = lock.impl;
    lock.impl = nullptr;
    return *this;
}

bool JFFoundation::JFSpinLock::TryLock() const
{
    auto lock = reinterpret_cast<Private::JFSpinLockImpl*>(impl);
    return lock->TryLock();
}

void JFFoundation::JFSpinLock::Lock() const
{
    auto lock = reinterpret_cast<Private::JFSpinLockImpl*>(impl);
    lock->Lock();
}

void JFFoundation::JFSpinLock::Unlock() const
{
    auto lock = reinterpret_cast<Private::JFSpinLockImpl*>(impl);
    lock->Unlock();
}
