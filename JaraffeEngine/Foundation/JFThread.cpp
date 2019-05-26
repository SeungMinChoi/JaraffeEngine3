#include "JFThread.h"
#include "JFSpinLock.h"
#include "JFCondition.h"
#include "JFScopeLock.h"

#include <process.h>

using namespace JFFoundation;

namespace Private
{
	struct ThreadParam
	{
		JFCondition condition;
		JFThread::ThreadID id;
		//JFThread::Runable runable;
	};

	unsigned int __stdcall ThreadHandler(void* p)
	{
		ThreadParam* threadParam = reinterpret_cast<ThreadParam*>(p);

		// Wait for calling thread 
		threadParam->condition.Lock();
		threadParam->condition.Sleep();

		// Set Id
		threadParam->id = ::GetCurrentThreadId();

		// Wake to calling thread
		threadParam->condition.Wake();
		threadParam->condition.Unlock();

		// copy
		//JFThread::Runable runable(threadParam->runable);

		// Thread run
		//runable.Invoke();

		// exit
		return 0;
	}
}

JFFoundation::JFThread::JFThread()
//JFFoundation::JFThread::JFThread(Runable _runable)
{
#if _WIN32
	// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/beginthread-beginthreadex?view=vs-2019

	Private::ThreadParam threadParam{ JFCondition(), 0 };
	//Private::ThreadParam threadParam{ JFCondition(), 0, _runable };
	
	handle = (HANDLE)::_beginthreadex(nullptr, 0, &Private::ThreadHandler, &threadParam, 0, &id);
	if (!handle)
	{
		const DWORD error = ::GetLastError();
		//throw std::runtime_error("Error 0x%X while trying to create thread", error);
	}

	// Wake for created thread
	threadParam.condition.Wake();

	// Wait for setting id
	threadParam.condition.Lock();
	threadParam.condition.Sleep();

	id = threadParam.id;

	threadParam.condition.Unlock();
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
