#pragma once

namespace JFFoundation
{
	template <int... indices>
	struct Index
	{};

	template <int Index, int... indices>
	struct IndexSequenceGeneration : IndexSequenceGeneration<Index - 1, Index - 1, indices...>
	{};

	template <int... indices>
	struct IndexSequenceGeneration<0, indices...> : Index<indices...>
	{};

	template<class... Types>
	class JFTypeTuple
	{
	public:
		enum { Count = sizeof...(Types) };

		// variadic template으로 받는 형태인경우 TypeList를 넣어줍니다.
		template<template<class...> class T>
		using InputTypes = T<Types...>;
	};
}