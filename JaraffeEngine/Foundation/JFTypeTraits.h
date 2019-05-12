#pragma once

#include "JFTypeListh.h"

namespace JFFoundation
{
	template <class>
	struct FunctionTraits {};

	// for function pointers
	template <class Return, class... Params>
	struct FunctionTraits<Return(*)(Params...)>
	{
		using ReturnType = Return;
		using ParamTypeList = JFTypeList<Params...>;

		using FunctionType = Return(*)(Params...);
	};

	// for pointers to member function
	template <class Class, class Return, class... Params>
	struct FunctionTraits<Return(Class::*)(Params...)>
	{
		using ReturnType = Return;
		using ParamTypeList = JFTypeList<Params...>;

		using FunctionType = Return(Class::*)(Params...);
	};
	template <class Class, class Return, class... Params>
	struct FunctionTraits<Return(Class::*)(Params...) const>
	{
		using ReturnType = Return;
		using ParamTypeList = JFTypeList<Params...>;

		using FunctionType = Return(Class::*)(Params...) const;
	};
}