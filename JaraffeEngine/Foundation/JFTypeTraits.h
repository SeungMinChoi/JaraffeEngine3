#pragma once

#include <type_traits>
#include "JFTypes.h"
#include "JFTypeTuple.h"

// http://www.cplusplus.com/reference/type_traits/
namespace JFFoundation
{
#pragma region FunctionTraits
	template <class Function>
	struct FunctionTraits;

	// for function pointers
	template <class Return, class... Params>
	struct FunctionTraits<Return(*)(Params...)>
	{
		using ReturnType = Return;
		using ParamTypeTuple = JFTypeTuple<Params...>;

		using FunctionType = Return(*)(Params...);
		using FunctionPrototype = Return(Params...);
	};

	// for pointers to member function
	template <class Class, class Return, class... Params>
	struct FunctionTraits<Return(Class::*)(Params...)>
	{
		using ClassType = Class;
		using ReturnType = Return;
		using ParamTypeTuple = JFTypeTuple<Params...>;

		using FunctionType = Return(Class::*)(Params...);
		using FunctionPrototype = Return(Params...);
	};
	template <class Class, class Return, class... Params>
	struct FunctionTraits<Return(Class::*)(Params...) const>
	{
		using ClassType = Class;
		using ReturnType = Return;
		using ParamTypeTuple = JFTypeTuple<Params...>;

		using FunctionType = Return(Class::*)(Params...) const;
		using FunctionPrototype = Return(Params...) const;
	};
#pragma endregion
#pragma region IsPointer
	template<class T>
	struct IsPointer
	{
		enum { Value = false };
	};
	template<class T>
	struct IsPointer<T*>
	{
		enum { Value = true };
	};
	template<class T>
	struct IsPointer<const T*>
	{
		enum { Value = true };
	};
#pragma endregion

#pragma region IsGlobalLambda
	template<class T>
	class IsGlobalLambda
	{
		using FunctionInfo = FunctionTraits<decltype(&T::operator())>;

		using ReturnType = typename FunctionInfo::ReturnType;
		using FunctionType = typename FunctionInfo::FunctionType;
		using ParamTypeTuple = typename FunctionInfo::ParamTypeTuple;

		template<class... Params> using GloabalLambdaType = ReturnType(*)(Params...);

		template<class ReturnType, class... Params> static JFTrue Test(ReturnType(*)(Params...));
		template<class ReturnType, class... Params> static JFFalse Test(...);

		template<class... Params> using TestType = decltype(Test<ReturnType, Params...>(0));
	public:
		enum { Value = ParamTypeTuple::InputTypes<TestType>::Value };
	};
#pragma endregion

#pragma region IsClass
	template<class T>
	class IsClass
	{
		template<class U> static JFTrue Test(int T::*);
		template<class U> static JFFalse Test(...);

	public:
		enum { Value = decltype(Test<T>(0))::Value };
	};
#pragma endregion

#pragma region IsCallable
	template<class T>
	class IsCallable
	{
		// operator가 private일땐 false. ( private일때도 굳이 확인하고 싶다면 상속을 이용. 근대 final이면?? )
		template<class U> static JFTrue Test(decltype(&U::operator())*);
		template<class U> static JFFalse Test(...);

	public:
		enum { Value = decltype(Test<T>(0))::Value };
	};
#pragma endregion

#pragma region IsPolymorphic
	// 해당 클래스가 virtual 함수를 가진 다형성 클래스인지 검사합니다.
	template<typename T>
	class IsPolymorphic
	{
		// Type 을 Value 로 사용하기 위한 함수
		template<class U> static U* MakePointer();

		// 다형성 클래스 라면 dynamic_cast 가 되어야 합니다.
		template<class U> static JFTrue Test(decltype(dynamic_cast<const volatile void*>(MakePointer<U>())));
		template<class U> static JFFalse Test(...);

	public:
		enum { Value = decltype(Test<T>(MakePointer<T>()))::Value };
	};
#pragma endregion
}