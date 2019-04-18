#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
	class JF_API JFString
	{
	public:
		JFString();
		JFString(const char* c);
		JFString(const JFString& s);
		JFString(JFString&& s) noexcept;

		~JFString();

	private:
		size_t CalcLen(const char* c);

		char* data;
	};
}
