#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
	class JF_API JFCondition
	{
	public:
		enum { DefaultWaitTime = MAXUINT };
		using MilliSecond = unsigned int;

		JFCondition();
		~JFCondition();

		JFCondition(JFCondition&& cond) noexcept;
		JFCondition& operator=(JFCondition&& cond) noexcept;

		void Lock();
		bool TryLock();
		void Unlock();

		void Sleep(MilliSecond wait = DefaultWaitTime);

		void Wake();
		void WakeAll();

	private:
		JFCondition(const JFCondition&) = delete;
		JFCondition& operator=(const JFCondition&) = delete;

	private:
		void* impl;
	};
}