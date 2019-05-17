#pragma once

namespace JFFoundation
{
	template<class... Types>
	class JFTypeTuple
	{
	public:
		// variadic template으로 받는 형태인경우 TypeList를 넣어줍니다.
		template<template<class...> class T>
		using InputTypes = T<Types...>;
	};
}