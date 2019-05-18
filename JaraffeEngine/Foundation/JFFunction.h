#pragma once

#include "JFTuple.h"
#include "JFTypeTraits.h"
#include <memory>

namespace JFFoundation
{
   //template <class Function>
   //class JFFunction
   //{
   //public:
	//	// User-defined deduction guides
   //    JFFunction(Function*);
   //};

	template<bool B, class Function>
	struct CastOperatorType;

	template<class Function>
	struct CastOperatorType<true, Function>
	{
		using Type = decltype(&Function::operator());
	};

	template<class Function>
	struct CastOperatorType<false, Function>
	{
		using Type = Function*;
	};

	template <class Function>
	class JFFunction
	{
		enum { IsCallable = IsCallable<Function>::Value };

		// Callable이 아니라면 GlobalFunction이므로 PointerType으로 받습니다.
		using FunctionRefType = typename JFConditional<IsCallable, Function, Function*>::Type;
		using FunctionRefType1 = typename JFConditional<IsCallable, CastOperatorType<true, Function>, CastOperatorType<false, Function>>::Type;

		//using FunctionInfo = 
		//	typename JFConditional<
		//		IsCallable<Function>::Value, 
		//		FunctionTraits<decltype(&Function::operator())>, 
		//		FunctionTraits<Function*>>::Type; //;
		//
		using FunctionType = FunctionTraits<typename FunctionRefType1::Type>;

		using RetrunType = typename FunctionType::ReturnType;
		using ParamTypeTuple = typename FunctionType::ParamTypeTuple;
	
	public:
		JFFunction(Function&& f)
			: func(f)
		{ }

		template<class... Params>
		RetrunType Invoke(Params... params)
		{
			return func(params...);
		}
	
	private:
		FunctionRefType func;
	};

}