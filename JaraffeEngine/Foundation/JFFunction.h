#pragma once

#include "JFTuple.h"
#include "JFTypeTraits.h"

namespace JFFoundation
{
	//template <class Return, class... Params>
	//struct JFFunctionInfo;
	//
	//template <class Return, class... Params>
	//struct JFFunctionInfo<Return(*)(Params...)>
	//{
	//	using ReturnType = Return;
	//	using Parameters = JFTuple<Params...>;
	//	using FunctionType = Return(*)(Params...);
	//};
	//
	//template <class Func, class Return, class... Params>
	//class JFFunctionInvoker
	//{
	//public:
	//	JFFunctionInvoker(Func&& fn)
	//		: func(fn)
	//	{}
	//
	//	Return operator () (Params... args)
	//	{
	//		return func(args...);
	//	}
	//
	//private:
	//	Func func;
	//};
	//
	//template <class Function>
	//class JFFunction
	//{
	//public:
	//	JFFunction(Function&& fn)
	//		: function(fn)
	//	{}
	//
	//	//typename JFFunctionInfo<Func>::ReturnType operator () const
	//	//{
	//	//}
	//
	//private:
	//	Function function;
	//	typename JFFunction<Function> func;
	//};

	template <class Function>
	class JFFunction
	{
	public:
		JFFunction(Function&& fn)
			: function(std::forward<Function>(fn))
		{}
		
		////typename FunctionTraits<Function>::ReturnType operator () (Params... args) const
		////{
		////	return function(args...);
		////}
		//
		Function operator * ()
		{
			return function;
		}

	private:
		Function function;
	};

}