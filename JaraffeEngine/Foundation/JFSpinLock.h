#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
    class JF_API JFSpinLock
    {
    public:
        using Count = DWORD;

        JFSpinLock(Count spinCount = 1024);
        ~JFSpinLock() noexcept;

        JFSpinLock(JFSpinLock&& lock) noexcept;
        JFSpinLock& operator=(JFSpinLock&& lock) noexcept;

        void Lock() const;
        bool TryLock() const;

        void Unlock() const;

    private:
        JFSpinLock(const JFSpinLock&) = delete;
        JFSpinLock& operator=(const JFSpinLock&) = delete;

    private:
        void* impl;
    };
}