#include "JFMatrix2.h"

using namespace JFFramework;

const JFMatrix2 JFFramework::JFMatrix2::Identity = JFMatrix2();

JFFramework::JFMatrix2::JFMatrix2()
	: _11(1), _12(0)
	, _21(0), _22(1)
{}

JFFramework::JFMatrix2::JFMatrix2(float s)
	: _11(s), _12(s)
	, _21(s), _22(s)
{}

JFFramework::JFMatrix2::JFMatrix2(float __11, float __12, 
								  float __21, float __22)
	: _11(__11), _12(__12)
	, _21(__21), _22(__22)
{}

JFMatrix2 JFFramework::JFMatrix2::operator*(const JFMatrix2& m) const
{
	return JFMatrix2();
}

JFMatrix2 JFFramework::JFMatrix2::operator+(const JFMatrix2& m) const
{
	return JFMatrix2();
}

JFMatrix2 JFFramework::JFMatrix2::operator-(const JFMatrix2& m) const
{
	return JFMatrix2();
}

JFMatrix2 JFFramework::JFMatrix2::operator*=(const JFMatrix2& m) const
{
	return JFMatrix2();
}

JFMatrix2 JFFramework::JFMatrix2::operator+=(const JFMatrix2& m) const
{
	return JFMatrix2();
}

JFMatrix2 JFFramework::JFMatrix2::operator-=(const JFMatrix2& m) const
{
	return JFMatrix2();
}
