#include "JFThread.h"
#include "JFSpinLock.h"
#include "JFCondition.h"
#include "JFScopeLock.h"

#include <process.h>

using namespace JFFoundation;

namespace Private
{


	unsigned int __stdcall ThreadHandler(void* p)
	{
		JFThread* thread = reinterpret_cast<JFThread*>(p);
		thread->id = ::GetCurrentThreadId();

		return 0;
	}
}

JFFoundation::JFThread::JFThread(Runable _runable)
	: runable(_runable)
{
#if _WIN32
	// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/beginthread-beginthreadex?view=vs-2019

	handle = (HANDLE)::_beginthreadex(nullptr, 0, &Private::ThreadHandler, this, 0, &id);
	if (!handle)
	{
		const DWORD error = ::GetLastError();
		//throw std::runtime_error("Error 0x%X while trying to create thread", error);
	}


#endif // _WIN32
}

JFFoundation::JFThread::~JFThread() noexcept
{
	CloseHandle(handle);
}

JFThread::ThreadID JFFoundation::JFThread::Id()
{
	return ::GetCurrentThreadId();
}
