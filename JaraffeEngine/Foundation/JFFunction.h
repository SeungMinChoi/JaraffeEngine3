#pragma once

#include "JFTuple.h"
#include "JFTypeTraits.h"

namespace JFFoundation
{
	namespace InternalImpl
	{
		template<class T, bool> struct CastRefType;
		template<class T> struct CastRefType<T, true>
		{
			using Type = T&;
		};
		template<class T> struct CastRefType<T, false>
		{
			using Type = T;
		};

		template<class Function, bool> struct CastFunctionOperatortype;
		template<class Function> struct CastFunctionOperatortype<Function, true>
		{
			using Type = decltype(&Function::operator());
		};
		template<class Function> struct CastFunctionOperatortype<Function, false>
		{
			using Type = 
				typename JFConditional<std::is_function<Function>::value, 
														 CastRefType<Function, false>, 
														 CastRefType<Function, false>>::Type::Type;
		};

		template<class Function>
		class DeduceFunctionTraits
		{
			using FunctionType = 
				typename JFConditional<IsCallable<Function>::Value, 
														CastFunctionOperatortype<Function, true>, 
														CastFunctionOperatortype<Function, false>>::Type::Type;

		public:
			using FunctionPrototype = typename FunctionTraits<FunctionType>::FunctionPrototype;
		};

        template<class ResultType, class... Params>
		struct Invoker
		{
		};

        template<class Function, class ResultType, class... Params>
		struct InvokerImpl : Invoker<ResultType, Params>
		{

		};
	}

	template<class FunctionProtoType>
	class JFFunction
	{
        using ReturnType = typename FunctionPrototypeTraits<FunctionProtoType>::ReturnType;
        using ParamTypeTuple = typename FunctionPrototypeTraits<FunctionProtoType>::ParamTypeTuple;

        template< using InvokerType = 
	public:
	    template<class Function>
		JFFunction(Function func)
		{

		}

    private:
        ParamTypeTuple::InputTypes<>
        InternalImpl::Invoker<ReturnType, >* invoker;
	};

	// Deduce signature
	template<class Function>
	JFFunction(Function) -> JFFunction<typename InternalImpl::DeduceFunctionTraits<Function>::FunctionPrototype>;
}