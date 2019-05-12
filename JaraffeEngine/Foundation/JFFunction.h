#pragma once

#include "JFTuple.h"
#include "JFTypeTraits.h"

namespace JFFoundation
{
	template <class Function, class ReturnType, class... Params>
	class JFFunctionInvoker
	{
	public:
		JFFunctionInvoker(Function&& fn) : function(fn) {}
	
		ReturnType Invoke(Params... params)
		{
			function(params...);
		}
	
	private:
		Function function;
	};
	
	template <class Function>
	class JFFunction
	{
		using Traits = FunctionTraits<decltype(&Function::operator())>; // 타입에따라 다르게 해야함..
		using ReturnType = typename Traits::ReturnType;
		using ParamTypeList = typename Traits::ParamTypeList;
		
		template<class... Params> using InvokerType = JFFunctionInvoker<Function, ReturnType, Params...>;
		using Invoker = typename ParamTypeList::template InputTypes<InvokerType>;
	
	public:
		JFFunction(Function&& fn) : invoker(fn) {}
	
		//ReturnType Invoke()
		//{
		//	invoker.Invoke();
		//}
	
	private:
		Invoker invoker;
	};
}