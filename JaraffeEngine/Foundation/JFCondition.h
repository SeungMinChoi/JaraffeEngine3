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
		JFCondition(JFCondition&& cond) noexcept;

		~JFCondition() noexcept;

		void Lock() const;
		bool TryLock() const;
		void Unlock() const;

		void Sleep(MilliSecond wait = DefaultWaitTime) const;

		void Wake()  const;
		void WakeAll() const;

	private:
		JFCondition(const JFCondition&) = delete;
		JFCondition& operator=(JFCondition&&) = delete;
		JFCondition& operator=(const JFCondition&) = delete;

	private:
		void* impl;
	};
}