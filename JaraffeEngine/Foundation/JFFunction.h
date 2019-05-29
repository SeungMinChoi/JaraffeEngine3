#pragma once

#include "JFTuple.h"
#include "JFTypeTraits.h"
#include "JFTypeTuple.h"

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

       
	}

    template<class ReturnType, class... Params>
    struct Invoker
    {
    };

    template<class Function, class ReturnType, class... Params>
    struct InvokerImpl : public Invoker<ReturnType, Params>
    {

    };

	template<class FunctionProtoType>
	class JFFunction
	{
        using FunctionInfo = FunctionPrototypeTraits<FunctionProtoType>;

        using ReturnType = typename FunctionInfo::ReturnType;
        using ParamTypeTuple = typename FunctionInfo::ParamTypeTuple;

        template<class... Params> using _InvokerType = Invoker<ReturnType, Params...>;
        //using InvokerType = ParamTypeTuple::InputTypes<_InvokerType>;

	public:
	    template<class Function>
		JFFunction(Function func)
		{

		}

    private:
        //InvokerType* invoker;
	};

	// Deduce signature
	template<class Function>
	JFFunction(Function) -> JFFunction<typename InternalImpl::DeduceFunctionTraits<Function>::FunctionPrototype>;
}