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

		using FunctionType = Return(Class::*)(Params...);
		using FunctionPrototype = Return(Params...);
	};
#pragma endregion

#pragma region FunctionPrototypeTraits
    template <class FunctionPrototype>
    struct FunctionPrototypeTraits
    {
        enum { Test = 0 };
    };

    template <class Return, class... Params>
    struct FunctionPrototypeTraits<Return(Params...)>
    {
        enum { Test = 1 };

        using ReturnType = Return;
        using ParamTypeTuple = JFTypeTuple<Params...>;

        using FunctionType = Return(*)(Params...);
        using FunctionPrototype = Return(Params...);
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
        using OpertorType = IsGlobalLambda<decltype(&T::operator())>;
        static T MakeInstance();
    
    public:
        enum { Value = decltype(OpertorType::Test( MakeInstance() ))::Value };
    };
    
    template<class Class, class ResultType, class... Params>
    class IsGlobalLambda<ResultType(Class::*)(Params...) const>
	{
    public:
        static JFTrue Test(ResultType(*)(Params...));
        static JFFalse Test(...);
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