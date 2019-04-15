#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
	class JF_API JFStringA
	{
	public:
		JFStringA();
		JFStringA(const char* c);
		JFStringA(const JFStringA& s);
		JFStringA(JFStringA&& s) noexcept;

		~JFStringA();

	private:
		size_t CalcLen(const char* c);

		char* data;
	};
}