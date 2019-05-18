#pragma once

namespace JFFoundation
{
#pragma region Template Basic Type
	template<bool B>
	struct JFBool
	{
		enum { Value = B };
	};
	using JFTrue = JFBool<true>;
	using JFFalse = JFBool<false>;

    template<int Num>
    struct JFNumber
    {
        enum { Value = Num };
    };
#pragma endregion


#pragma region Conditional
    template<bool B, class T, class F>
    struct JFConditional;

	template<class T, class F>
    struct JFConditional<1, T, F>
    {
		using Type = T;
    };
    template<class T, class F>
    struct JFConditional<0, T, F>
    {
		using Type = F;
    };
#pragma endregion
}