#pragma once

namespace JFFoundation
{
	template <class Function>
	struct FunctionTraits;

	// for function pointers
	template <typename Return, typename... Params>
	struct FunctionTraits<Return(*)(Params...)>
	{
		using FunctionType = Return(*)(Params...);
	};

	// for pointers to member function
	template <class Class, class Return, class... Params>
	struct FunctionTraits<Return(Class::*)(Params...)>
	{
		using FunctionType = Return(Class::*)(Params...);
	};
	template <class Class, class Return, class... Params>
	struct FunctionTraits<Return(Class::*)(Params...) const>
	{
		using FunctionType = Return(Class::*)(Params...) const;
	};
}