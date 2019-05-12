#pragma once

namespace JFFoundation
{
	template<int Num>
	struct JFNumber
	{
		enum { Value = Num };
	};

	template<bool B, class T, class F>
	struct JFConditional;

	template<class T, class F>
	struct JFConditional<1, T, F>
	{
		enum{ Type = T };
	};
	template<class T, class F>
	struct JFConditional<0, T, F>
	{
		enum { Type = F };
	};
}