#pragma once

#include "JFObject.h"
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
			using Type = std::remove_reference_t<T>;
		};

        template<class Function, bool> struct CastFunctionOperatortype;
        template<class Function> struct CastFunctionOperatortype<Function, true>
        {
            using Type = decltype(&Function::operator());
        };
        template<class Function> struct CastFunctionOperatortype<Function, false>
        {
            using Type = Function;
        };

		template<class Function>
		class DeduceFunctionTraits
		{
        public:
            using FunctionType = typename CastFunctionOperatortype<Function,  std::is_class_v<Function>>::Type;

		public:
			using FunctionPrototype = typename FunctionTraits<FunctionType>::FunctionPrototype;
		};

        // VTable 도 제거하고 싶은대.. 일단 아이디어가 떠오를때까진 이렇게..
        // ( 사실 메모리풀 만들면 그렇기 신경 안써도 될 듯. )
        template<class ReturnType, class... Params>
        class Invoker
        {
        public:
            virtual ReturnType Invoke(Params... Param){}
        };

        template<class Function, class ReturnType, class... Params>
        class InvokerImpl : public Invoker<ReturnType, Params...>
        {
            // class가 아니라면 RefType으로
            using FunctionRef = typename CastRefType<Function, !std::is_class_v<Function>>::Type;

        public:
            InvokerImpl(Function f)
                : func(f)
            {}
            
            ReturnType Invoke(Params... Param) override
            {
                return func(Param...);
            }

        private:
            Function func;
        };
	}

    // TODO : ProtoType과 FunctionType을 같이 못다루는 약점을 개선해야함
	template<class FunctionProtoType>
	class JFFunction
	{
        using FunctionInfo = FunctionPrototypeTraits<FunctionProtoType>;
        using ReturnType = typename FunctionInfo::ReturnType;
        using ParamTypeTuple = typename FunctionInfo::ParamTypeTuple;

        template<class... Params> using _InvokerType = InternalImpl::Invoker<ReturnType, Params...>;
        using InvokerType = typename ParamTypeTuple::template InputTypes<_InvokerType>;

        template<class Function, class... Params> using _InvokerImplType = InternalImpl::InvokerImpl<Function, ReturnType, Params...>;

	public:
        JFFunction(){}
	    
        template<class Function>
		JFFunction(Function func)
		{
            // TODO : 메모리풀 만들면 변경해줘야함.
            using InvokerImplType = typename ParamTypeTuple::template InputTypes<_InvokerImplType, Function>;
            invoker = new InvokerImplType(std::forward<Function>(func));
		}

        // TODO : 약점 개선되면 Deep copy로 변경해야함
        JFFunction(const JFFunction& function)
        {
            invoker = function.invoker;
        }

        // TODO : 약점 개선되면 Deep copy로 변경해야함
        JFFunction(JFFunction&& rhs) noexcept
            : invoker(rhs.invoker)
        {
            rhs.invoker = nullptr;
        }

        template<class Function>
        JFFunction& operator = (Function func)
        {
            using InvokerImplType = typename ParamTypeTuple::template InputTypes<_InvokerImplType, Function>;
            invoker = new InvokerImplType(std::forward<Function>(func));
            return *this;
        }

        // TODO : 약점 개선되면 Deep copy로 변경해야함
        JFFunction& operator = (const JFFunction& function)
        {
            invoker = function.invoker;
            return *this;
        }

        JFFunction& operator = (JFFunction&& rhs) noexcept
        {
            invoker = rhs.invoker;
            rhs.invoker = nullptr;
            return *this;
        }

        // TODO : 이것도 해결해야함.
        template<class... Params>
        ReturnType Invoke(Params... params)
        {
            assert(invoker);
            if (invoker)
            {
                invoker->Invoke(params...);
            }
        }

    private:
        JFObject<InvokerType> invoker;
	};

	// Deduce signature
	template<class Function>
	JFFunction(Function) -> JFFunction<typename InternalImpl::DeduceFunctionTraits<Function>::FunctionPrototype>;
}