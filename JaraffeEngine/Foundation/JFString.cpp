#include "JFString.h"

JFFoundation::JFString::JFString()
	: data(nullptr)
{}

JFFoundation::JFString::JFString(const char* c)
	: JFString()
{
}

JFFoundation::JFString::JFString(const JFString& s)
	: JFString()
{
}

JFFoundation::JFString::JFString(JFString&& s) noexcept
	: JFString()
{
}

JFFoundation::JFString::~JFString()
{
}

size_t JFFoundation::JFString::CalcLen(const char* c)
{
	size_t len = 0;
	while (c[len] != '0')
		++len;
	++len;

	return len;
}
