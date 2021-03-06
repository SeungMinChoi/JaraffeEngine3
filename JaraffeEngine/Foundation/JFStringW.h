#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
	class JF_API JFStringW
	{
	public:
		enum { All = -1 };

		JFStringW();
		JFStringW(const wchar_t* c, size_t len = All);
		JFStringW(const JFStringW& str);
		JFStringW(JFStringW&& str) noexcept;
		~JFStringW();

		void Clear();
		void Reverse();

		JFStringW& Append(const JFStringW& str);
		JFStringW& Append(const wchar_t* c, size_t len = All);
		JFStringW& Erase(size_t pos = 0, size_t len = All);

		size_t Length() const;
		const wchar_t* Str() const;

		JFStringW& operator = (const wchar_t* c);
		JFStringW& operator = (const JFStringW& str);
		JFStringW& operator = (JFStringW&& str);

	private:
		wchar_t* data;
	};
}
