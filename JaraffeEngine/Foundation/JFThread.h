#pragma once

#include "../JFInclude.h"
#include "JFFunction.h"

namespace JFFoundation
{
	// TODO : Event, Lock, Runable 객체 만들고 나머지 만들기.
	class JF_API JFThread
	{
	public:
		using ThreadID = unsigned int;
		using Runable = JFFunction<void()>;

        JFThread(Runable runable);
        ~JFThread() noexcept;

        //native_handle
		ThreadID Id();

	private:
		JFThread(JFThread&&) = delete;
		JFThread(const JFThread&) = delete;
		JFThread& operator=(const JFThread&) = delete;
		JFThread& operator=(JFThread&&) = delete;

	private:
		ThreadID id = 0;
		void* handle = nullptr;
		
		Runable runable;
	};
}