#include "JFThread.h"
#include <process.h>

using namespace JFFoundation;

namespace Private
{
	struct ThreadParam
	{
		JFThread::ThreadID id;
	};

	unsigned int __stdcall ThreadHandler(void* p)
	{
		ThreadParam* thread = reinterpret_cast<ThreadParam*>(p);
		thread->id = ::GetCurrentThreadId();

		return 0;
	}
}

JFFoundation::JFThread::JFThread(Runable _runable)
	: runable(_runable)
{
#if _WIN32
	// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/beginthread-beginthreadex?view=vs-2019

	Private::ThreadParam param;
	//param.runable = fn;

	handle = (HANDLE)::_beginthreadex(nullptr, 0, &Private::ThreadHandler, &param, 0, &id);
	if (!handle)
	{
		const DWORD error = ::GetLastError();
		//throw std::runtime_error("Error 0x%X while trying to create thread", error);
	}


	//::WaitForSingleObject(handle, INFINITE);

	id = param.id;

#endif // _WIN32
}

JFFoundation::JFThread::~JFThread() noexcept
{
}

JFThread::ThreadID JFFoundation::JFThread::Id()
{
	return ::GetCurrentThreadId();
}
