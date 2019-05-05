#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
	// TODO : Event, Lock, Runable 객체 만들고 나머지 만들기.
	class JF_API JFThread
	{
	public:
		using ThreadID = unsigned int;

        //template<class FUNC, class ...ARGS>
        //explicit JFThread(FUNC&& fn, ARGS&&... args)
        //{
        //    auto as = std::make_tuple(args...);
        //    invoke(fn, as, std::make_index_sequence<decltype(as)>);
        //}
        //
        //template<class FUNC, class TUPLE, class ...INDICES>
        //void invoke(FUNC&& fn, TUPLE&& tuple, INDICES&&... i)
        //{
        //    std::invoke(fn, std::get<i>(tuple)...);
        //}

        JFThread();
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
	};
}