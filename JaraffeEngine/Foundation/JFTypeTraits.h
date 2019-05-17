#pragma once

#include "JFTypeTuple.h"

namespace JFFoundation
{
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

#pragma region FunctionTraits
	template <class Function>
    struct FunctionTraits;

	// for function pointers
	template <class Return, class... Params>
	struct FunctionTraits<Return(*)(Params...)>
	{
		using ReturnType = Return;
		using ParamTypeList = JFTypeTuple<Params...>;

		using FunctionType = Return(*)(Params...);
	};

	// for pointers to member function
	template <class Class, class Return, class... Params>
	struct FunctionTraits<Return(Class::*)(Params...)>
	{
		using ReturnType = Return;
		using ParamTypeList = JFTypeTuple<Params...>;

		using FunctionType = Return(Class::*)(Params...);
	};
	template <class Class, class Return, class... Params>
	struct FunctionTraits<Return(Class::*)(Params...) const>
	{
		using ReturnType = Return;
		using ParamTypeList = JFTypeTuple<Params...>;

		using FunctionType = Return(Class::*)(Params...) const;
	};
#pragma endregion
}