#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
	// https://stackoverflow.com/questions/13509733/what-is-the-use-of-wchar-t-in-general-programming
	// https://stackoverflow.com/questions/3951722/whats-the-difference-between-unicode-and-utf-8/13212528#13212528
	// UTF - 8 is an encoding - Unicode is a character set
	class JF_API JFStringW
	{
	public:
		JFStringW();
		JFStringW(const wchar_t* c);
		JFStringW(const JFStringW& s);
		JFStringW(JFStringW&& s) noexcept;

		~JFStringW();

	private:
		size_t CalcLen(const wchar_t* c);

		wchar_t* data;
	};
}