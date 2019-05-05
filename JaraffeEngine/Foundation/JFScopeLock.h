#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
    template<class LOCK>
    class JFScopeLock
    {
    public:
        JFScopeLock(const LOCK& l)
            : lock(l)
        {
            lock.Lock();
        }
        
        ~JFScopeLock() noexcept
        {
            lock.Unlock();
        }

    private:
        JFScopeLock(JFScopeLock&&) = delete;
        JFScopeLock(const JFScopeLock&) = delete;
        JFScopeLock& operator=(const JFScopeLock&) = delete;
        JFScopeLock& operator=(JFScopeLock&&) = delete;

    private:
        const LOCK& lock;
    };
}