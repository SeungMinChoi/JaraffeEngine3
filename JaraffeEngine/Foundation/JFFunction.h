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
			using Type = typename JFConditional<std::is_function<Function>::value, Function, Function&>::Type;
		};

		template<class Function>
		class DeduceFunctionTraits
		{
			using FunctionType = typename JFConditional<IsCallable<Function>::Value, 
														typename CastFunctionOperatortype<Function, true>::Type, 
														typename CastFunctionOperatortype<Function, false>::Type>::Type;

		public:
			using FunctionPrototype = typename FunctionTraits<FunctionType>::FunctionPrototype;
		};

		struct Invoker
		{
		};

		template<class Function>
		struct InvokerImpl
		{

		};
	}

	template<class FunctionProtoType>
	class JFFunction
	{
	public:
		template<class Function>
		JFFunction(Function func)
		{

		}
	};

	// Deduce signature
	template<class Function>
	JFFunction(Function) -> JFFunction<typename InternalImpl::DeduceFunctionTraits<Function>::FunctionPrototype>;
}