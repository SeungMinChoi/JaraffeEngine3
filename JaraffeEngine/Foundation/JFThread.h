#pragma once

#include "../JFInclude.h"
#include "JFFunction.h"

namespace JFFoundation
{
	class JF_API JFThread
	{
	public:
		//using Runable = JFFunction<void()>;
		using ThreadID = unsigned int;
		using NativeHandle = void*;

        //JFThread(Runable runable);
		JFThread();
        ~JFThread() noexcept;

		ThreadID Id();

	private:
		JFThread(JFThread&&) = delete;
		JFThread(const JFThread&) = delete;
		JFThread& operator=(const JFThread&) = delete;
		JFThread& operator=(JFThread&&) = delete;

	private:
		ThreadID id = 0;
		NativeHandle handle = nullptr;
	};
}