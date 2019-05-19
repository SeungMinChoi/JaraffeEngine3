#pragma once

#include "JFTuple.h"
#include "JFTypeTraits.h"

namespace JFFoundation
{
	namespace Helper
	{
		template<bool B, class Function>
		struct CastFunctionOperatorType;

		template<class Function>
		struct CastFunctionOperatorType<true, Function>
		{
			using Type = decltype(&Function::operator());
		};

		template<class Function>
		struct CastFunctionOperatorType<false, Function>
		{
			using Type = Function * ;
		};
	}

	//template <class Function>
	//class JFFunction
	//{
	//public:
	//	// User-defined deduction guides
	//	JFFunction(Function*);
	//};

	// for GlobalFunction
	template <class Function>
	class JFFunction
	{
		enum { IsCallable = IsCallable<Function>::Value };

		// Callable이 아니라면 GlobalFunction이므로 PointerType으로 받습니다.
		using FunctionRefType = typename JFConditional<IsCallable, Function, Function*>::Type;

		// FunctionTraits가능한 Type으로 변환해 줍니다.
		using FunctionOperatorType = 
			typename JFConditional<IsCallable, 
				Helper::CastFunctionOperatorType<true, Function>, 
				Helper::CastFunctionOperatorType<false, Function>>::Type;

		// Function Info
		using FunctionInfo = FunctionTraits<typename FunctionOperatorType::Type>;

		using RetrunType = typename FunctionInfo::ReturnType;
		using ParamTypeTuple = typename FunctionInfo::ParamTypeTuple;
	
	public:
		JFFunction(Function&& f)
			: func(f)
		{}

		template<class... Params>
		RetrunType Invoke(Params... params)
		{
			return func(params...);
		}

	private:
		FunctionRefType func;
	};

	// TODO : 일단MemberFunction은 좋은 아이디어가 생길때 까진 이렇게 사용.
	// ClassType은 SmartPointer로 받도록 하기

	// for ClassMemberFunction 
	template<class Function>
	struct JFClassFunction
	{
		using ClassType = typename FunctionTraits<Function>::ClassType;
		using ReturnType = typename FunctionTraits<Function>::ReturnType;
		using FunctionType = typename FunctionTraits<Function>::FunctionType;
	
		JFClassFunction(Function&& f, ClassType* c)
			: func(f)
			, classPointer(c)
		{}
	
		template<class... Params>
		ReturnType Invoke(Params... params)
		{
			return (classPointer->*func)(params...);
		}
	
	private:
		Function func;
		ClassType* classPointer;
	};
}