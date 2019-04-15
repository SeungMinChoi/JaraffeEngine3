#include "JFStringA.h"

JFFoundation::JFStringA::JFStringA()
	: data(nullptr)
{}

JFFoundation::JFStringA::JFStringA(const char* c)
	: JFStringA()
{
}

JFFoundation::JFStringA::JFStringA(const JFStringA& s)
	: JFStringA()
{
}

JFFoundation::JFStringA::JFStringA(JFStringA&& s) noexcept
	: JFStringA()
{
}

JFFoundation::JFStringA::~JFStringA()
{
}

size_t JFFoundation::JFStringA::CalcLen(const char* c)
{
	size_t len = 0;
	while (c[len] != '0')
		++len;
	++len;

	return len;
}
