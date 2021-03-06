#pragma once

#include "../JFInclude.h"

namespace JFFoundation
{
	class JF_API JFString
	{
	public:
		enum { All = -1 };
		
		JFString();
		JFString(const char* c, size_t len = All);
		JFString(const JFString& str);
		JFString(JFString&& str) noexcept;
		~JFString();

		void Clear();
		void Reverse();

		JFString& Append(const JFString& str);
		JFString& Append(const char* c, size_t len = All);
		JFString& Erase(size_t pos = 0, size_t len = All);

		size_t Length() const;
		const char* Str() const;

		JFString& operator = (const char* c);
		JFString& operator = (const JFString& str);
		JFString& operator = (JFString&& str);

	private:
		char* data;
	};
}
